#include "VirtMemSim.h"

////////////////////
// CONFIGURAÇÃO
////////////////////
#define ALGO "Relogio" // LRU ou Relogio
#define TAM_MEM_FIS 128
#define TAM_PAG 3

// TODO: Parametrizar no código essas constantes
#define TAM_QUAD_PAG 22
#define TAM_END_LOG 33
#define TAM_MAX_MEM_SEC 55
#define TAM_MAX_IMG_PROC 66

#define R_ACESS 1111
#define W_ACESS 2222
#define CPU_ACESS 3333
#define IO_ACESS 4444

////////////////////
// VARIÁVEIS GLOBAIS
////////////////////
// Processos carregados a partir do input.txt e criados com a operação C
// Este vetor contém em cada termo um vetor com o idProcesso e tamanho
vector<vector<int> > processosEntrada;

// Lista de operações que exigem requisição (R, W, P ou I)
// Este vetor contém em cada termo um vetor com o idProcesso e valor (endereço)
vector<vector<int> > listaRequisicoes;

// Lista contendo os processos carregados do input.txt no formato da classe Processo
vector<Processo*> listaDeProcessos;

// Um deque contendo os elementos da memória principal. O deque foi utilizado dada a necessidade de alguns algoritmos de remover elementos nos dois extremos
deque<deque<Pagina*> > memoriaPrincipal;

// Representação da memória virtual na simulação
// É representada por em vetor de vetores de páginas, que por sua vez contém cada processo.
vector<vector<Pagina*> > memoriaVirtual;

// Mapeamento do ID de entrada no input.txt para o ID de execução
map<int, int> mapaIDsProc;

// Quantidade de trocas de páginas durante toda a simulação
int qtdSwapsPaginas = 0;

// Quantidade de faltas de páginas durante toda a simulação
int qtdFaltaPag = 0;

////////////////////
// FUNÇÕES DE ENTRADA
////////////////////

// Método para ler entrada crua
tuple_list leEntrada(const char * caminhoArquivo) {
  tuple_list entrada;
  ifstream arqEntrada(caminhoArquivo);
  string idProcesso, valor;
  char operacao;

  while (arqEntrada >> idProcesso >> operacao >> valor) {
    entrada.push_back({idProcesso, operacao, valor});
  }

  return entrada;
}

// Impressão da entrada
void imprimeEntrada(parsed_tuple_list entrada) {
  for(const auto &i : entrada) {
    cout << get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << endl;
  }
}

// Método para interpretar valores de entrada
parsed_tuple_list parseiaEntrada(tuple_list entrada) {
  parsed_tuple_list entradaParseada;
  string parserBuffer;
  int valor, idProcesso;
  unsigned primeiroCar, ultimoCar;
  string marcaInicial = "(";
  string marcaFinal = ")2";

  for(const auto &i : entrada) {
    parserBuffer = get<0>(i);
    size_t j = 0;
    for ( ; j < parserBuffer.length(); j++ ){ if ( isdigit(parserBuffer[j]) ) break; };
    parserBuffer = parserBuffer.substr(j, parserBuffer.length() - j );
    idProcesso = atoi(parserBuffer.c_str());

    if (get<1>(i) == 'C') {
      valor = stoi(get<2>(i));
      entradaParseada.push_back({idProcesso, get<1>(i), valor});
    } else {
      primeiroCar = get<2>(i).find(marcaInicial);
      ultimoCar = get<2>(i).find(marcaFinal);
      parserBuffer = get<2>(i).substr(primeiroCar + 1, ultimoCar - 1);
      valor = stoi(parserBuffer);
      entradaParseada.push_back({idProcesso, get<1>(i), valor});
    } 
  }
  
  return entradaParseada;
}

// Imprime o tipo de acesso na tela de acordo com o parâmentro informado.
void ExibirTipoAcesso(int tipoAcesso) {
  switch (tipoAcesso) {
    case CPU_ACESS:
      cout << "> Tipo de acesso: Processo executando na CPU" << "\n\n";
      break;

    case IO_ACESS:
      cout << "> Tipo de acesso: Processo executando E/S" << "\n\n";
      break;
    
    case R_ACESS:
      cout << "> Tipo de acesso: leitura" << "\n\n";
      break;

    case W_ACESS:
      cout << "> Tipo de acesso: escrita" << "\n\n";
      break;
  }
}

// O LRU percorre as requisições feitas pelos processos. Com o intuíto de remover sempre o quadro do topo do deque (LRU), 
// as páginas foram inicializadas com LRU de tempo = 0.
void LRU(int tamPaginas, int qtdQuadros) {
  cout << ">>>>>>>>>>>>>>>>>>" << endl;
  cout << ">>>> LRU acionado" << endl;
  cout << ">>>>>>>>>>>>>>>>>>" << endl;
  cout << ">> Quantidade de quadros: " << qtdQuadros << endl;
  cout << ">> Tamanho das páginas: " << tamPaginas << endl;
  int idProcesso; // idProcesso se refere ao id de processamento interno e não ao lido (e.g. P7)
  int tipoAcesso; // Tipo de acesso a depender do tipo de operação utilizada (i.e., R. W, P ou I)
  int endMem; // endereço de memória chamado pela requisição
  int endUsadoRecent; // O endereço que foi utilizado mais recentemente
  Pagina* paginaRequisitada; // página requisitada durante a operação
  
  for (int i = 0; i < listaRequisicoes.size(); i++) {
    cout << ">> Iteração: " << i << endl;

    idProcesso = listaRequisicoes[i][0]; // Recupera o idProcesso
    cout << "> ID do processo: " << idProcesso << endl;

    endMem = listaRequisicoes[i][1]; // Recupera o endereço de memória a ser usado na requisição
    cout << "> Endereço de memória: " << endMem << endl;

    // Verifica se a página não pode ser acessada
    if (abs((endMem-1)/tamPaginas) > memoriaVirtual[idProcesso].size()) {
      cout << "> Processo: " << idProcesso << " requisitando página número: " << abs((endMem-1)/tamPaginas) << endl;
      cout << "> Ocorreu uma falta de página" << "\n\n";
      qtdFaltaPag++;
      continue;
    }

    paginaRequisitada = memoriaVirtual[idProcesso][abs((endMem-1)/tamPaginas)];

    tipoAcesso = listaRequisicoes[i][2];
    ExibirTipoAcesso(tipoAcesso);

    if ((tipoAcesso == R_ACESS) || (tipoAcesso == W_ACESS)) {
      cout << "> Processo: " << idProcesso << " requisitando página número: " << abs((endMem-1)/tamPaginas) << endl;
    
      // Verfica se a página existe na memória
      if (paginaRequisitada->bitAlocacaoMemoria == 0) {
        cout << "> Pagina solicitada NÃO está contida na memória principal" << endl;
        // Se houver espaço livre carrega a página na memória
        if (memoriaPrincipal[idProcesso].size() < qtdQuadros) {
          cout << "> Há espaço livre na memória" << endl;
          memoriaPrincipal[idProcesso].push_back(paginaRequisitada);
          cout << "> Inserindo página requisitada" << endl;
        }
        // Se não houver espaço livre, faz o swap da página
        else {
          cout << "> Não há espaço livre na memória principal" << endl;
          memoriaPrincipal[idProcesso].front()->bitAlocacaoMemoria = 0; // Define o bit de alocação de memória para zero, uma vez que a página será apagada
          memoriaPrincipal[idProcesso].pop_front(); // Remove o menos utilizado recentemente
          memoriaPrincipal[idProcesso].push_back(paginaRequisitada); // Insere a página recementemente usada no final do deck da memória principal
          cout << "> Ocorreu um swap de página" << endl;
          qtdSwapsPaginas++;
        }
        paginaRequisitada->bitAlocacaoMemoria = 1; // A página foi alocada na memória
        cout << "> Página alocada com sucesso" << endl;
      }
      // Se a página já estiver na memória principal
      else {
        cout << "> Página solicitada ESTÁ na memória principal" << endl;
        for (int j = 0; j < memoriaPrincipal[idProcesso].size(); j++) {
          if (memoriaPrincipal[idProcesso][j]->idPagina == paginaRequisitada->idPagina) {
              endUsadoRecent = j;
              cout << "> Encontrou a página na memória: " << endUsadoRecent << endl;
              break;
          }
        }
        // Apaga a página requisitada da memória principal
        memoriaPrincipal[idProcesso].erase(memoriaPrincipal[idProcesso].begin() + endUsadoRecent);
        cout << "> Página apagada do endereço requisitado" << endl;
        memoriaPrincipal[idProcesso].push_back(paginaRequisitada); // Insere na memória principal
        cout << "> Página inserida no endereço requisitado" << endl;
      }
      cout << endl;
    }
  } 
}

void Relogio(int tamPaginas, int qtdQuadros) {
  cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
  cout << ">>>> Algoritmo Relógio acionado" << endl;
  cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
  cout << ">> Quantidade de quadros: " << qtdQuadros << endl;
  cout << ">> Tamanho das páginas: " << tamPaginas << endl;
  int idProcesso; // idProcesso se refere ao id de processamento interno e não ao lido (e.g. P7)
  int tipoAcesso; // Tipo de acesso a depender do tipo de operação utilizada (i.e., R. W, P ou I)
  int endMem; // endereço de memória chamado pela requisição
  int endUsadoRecent; // O endereço que foi utilizado mais recentemente
  int numPagInicial; // Define o ponteiro do relógio que foi inicialmente carregado.
  int numPagAtual = 0; // Define o ponteiro atual do relógio.
  bool paginaEncontrada = false; // booleano de status para a página com o bit referencia igual a 0 foi encontrado.
  Pagina* paginaRequisitada; // página requisitada durante a operação
  Pagina* paginaRelogio; // página atual do relógio

  for (int i = 0; i < listaRequisicoes.size(); i++) {
    paginaEncontrada = false; // Verifica se o bit de referencia é igual a 0.
    idProcesso = listaRequisicoes[i][0]; // Recupera o ID do processo.
    endMem = listaRequisicoes[i][1]; // endereço de memória chamado pela requisição
    paginaRequisitada = memoriaVirtual[idProcesso][abs((endMem-1)/tamPaginas)]; // página requisitada durante a operação 
    paginaRelogio = memoriaPrincipal[idProcesso][numPagAtual]; // página atual selecionada pelo algoritmo do relógio.

    cout << ">> Iteração: " << i << endl;
    cout << "> ID do processo: " << idProcesso << endl;
    cout << "> Endereço de memória: " << endMem << endl;

    // Verifica se a página não pode ser acessada
    if (abs((endMem-1)/tamPaginas) > memoriaVirtual[idProcesso].size()) {
      cout << "> Processo: " << idProcesso << " requisitando página número: " << abs((endMem-1)/tamPaginas) << endl;
      cout << "> Ocorreu uma falta de página" << "\n\n";
      qtdFaltaPag++;
      continue;
    }

    // Exibe o tipo de acesso que está sendo realizado.
    tipoAcesso = listaRequisicoes[i][2];
    ExibirTipoAcesso(listaRequisicoes[i][2]);

    if ((tipoAcesso == R_ACESS) || (tipoAcesso == W_ACESS)) {
      
      // Verifica se a página está alocada na memória.
      if (paginaRequisitada->bitAlocacaoMemoria == 0) {
        cout << "> Pagina solicitada NÃO está contida na memória principal" << endl;

        if (memoriaPrincipal[idProcesso].size() < qtdQuadros) {
          // Se existir quadros na memória disponivel, então a página é adicionada na memória.
          cout << "> Há espaço livre na memória" << endl;
          memoriaPrincipal[idProcesso].push_back(paginaRequisitada);
          cout << "> Inserindo página requisitada" << endl;
        } else {
          // Senão, é aplicado o algoritmo de substituição de página.
          cout << "> Não há espaço de memória live, procurando página com o bit de referencia = 0" << endl;

          while (paginaEncontrada == false) {
            numPagInicial = numPagAtual;

            // Se o bit de referencia for igual a 0, a página é selecionada para substituição de página.
            if (paginaRelogio->bitReferencia == 0) {
              cout << "> Página para substituição encontrada." << endl;
              paginaRelogio->bitAlocacaoMemoria = 0;
              memoriaPrincipal[idProcesso][numPagAtual] = paginaRequisitada;
              paginaRequisitada->bitAlocacaoMemoria = 1;
              cout << "> Página substituida." << endl;
              qtdSwapsPaginas++;
              paginaEncontrada = true;
            }

            // Se o bit de referencia for igual a 1, então é atribuido 0 para esse valor como forma de validar a utilização recente dessa página.
            if (paginaRelogio->bitReferencia == 1) {
              paginaRelogio->bitReferencia = 0;
            }
            
            numPagAtual++;
            if (numPagAtual == memoriaPrincipal[idProcesso].size()) {
              numPagAtual = 0;
            }

            paginaRelogio = memoriaPrincipal[idProcesso][numPagAtual];
            // Se o número da página atual for igual ao número da página inicial do algoritmo. Então a pagina inicial é removida.
            if (numPagAtual == numPagInicial) {
              cout << "> Página para substituição encontrada." << endl;
              paginaRelogio->bitAlocacaoMemoria = 0;
              memoriaPrincipal[idProcesso][numPagAtual] = paginaRequisitada;
              paginaRequisitada->bitAlocacaoMemoria = 1;
              cout << "> Página substituida." << endl;
              qtdSwapsPaginas++;
              paginaEncontrada = true;
            }
          }
        }
      } else {
        // Caso a página esteja na memória principal o bit de referencia é atualizado.
        cout << "> Pagina solicitada está contida na memória principal" << endl;
        memoriaVirtual[idProcesso][abs((endMem-1)/tamPaginas)]->bitReferencia = 1;
      }
    }
  }
}

int main(int argc, char * const argv[]) {
  // Verifica se a entrada possui a quantidade correta de argumentos
  if (argc != 2) {
    cerr << ">>> ERRO: Quantidade inválida de argumentos" << endl;
    return 1;
  }

  // Verifica a configuração do algoritmo a ser utilizado
  if ((ALGO != "LRU") && (ALGO != "Relogio")) {
    cerr << ">>> ERRO: Algoritmo inválido: " << ALGO << endl;
    return 1;
  }

  // Leitura da entrada
  tuple_list entrada = leEntrada(argv[1]);
  parsed_tuple_list entradaParseada = parseiaEntrada(entrada);

  cout << ">>>>>>>>>>>>>>>>>>>>>>>" << endl;
  cout << ">>>> ENTRADA PARSEADA" << endl;
  cout << ">>>>>>>>>>>>>>>>>>>>>>>" << endl;

  imprimeEntrada(entradaParseada);
  cout << endl;

  // Parâmetros de entrada
  int idProcesso; 
  int tamMemProcesso;
  int endProcesso;

   // Inicialização de variáveis
  int qtdQuadrosMemPrincipal = TAM_MEM_FIS/TAM_PAG;
  int qtdQuadros = 0;
  int contadorProc = 0;
  int contadorReq = 0;

  // Percorre a entrada parseada com o objetivo de popular a memória e chamar o algoritmo de paginação
  for(const auto &i : entradaParseada) {
    idProcesso = get<0>(i);

    // Vetores utilizados como buffer
    vector<int> processos, endMemoria;

    // Caso a operação seja C, cria o processo
    if (get<1>(i) == 'C') {
      tamMemProcesso = get<2>(i);
      cout << ">> Criando processo com ID: " << idProcesso << endl;
      processos.push_back(contadorProc);
      processos.push_back(tamMemProcesso);
      processosEntrada.push_back(processos);
      mapaIDsProc.insert(pair<int, int>(idProcesso, contadorProc)); 
      listaDeProcessos.push_back(new Processo(contadorProc, tamMemProcesso, TAM_PAG));
      contadorProc++;
    }
    // Caso a operação seja de outro tipo, inicia as rotinas para tratar as requisições
    else {
      cout << ">> Iniciando processo de tratamento da requisição para o processo ID: " << idProcesso << endl;
      endProcesso = get<2>(i);
      endMemoria.push_back(mapaIDsProc[idProcesso]); // id da requisicao
      endMemoria.push_back(endProcesso);

      contadorReq++;

      switch(get<1>(i)) {
        case 'R':
        cout << "> Requisitando acesso de LEITURA ao endereço=(" << endProcesso << ")2" << "\n\n";
          endMemoria.push_back(R_ACESS);
          break;
        case 'W':
          cout << "> Requisitando acesso de ESCRITA ao endereço=(" << endProcesso << ")2" << "\n\n";
          endMemoria.push_back(W_ACESS);
          break;
        case 'P':
          cout << "> Requisitando processamento na CPU da instrução do endereço=(" << endProcesso << ")2" << "\n\n";
          endMemoria.push_back(CPU_ACESS);
          break;
        case 'I':
        cout << "> Requisitando execução de chamada IO com a instrução do endereço=(" << endProcesso << ")2" << "\n\n";
          endMemoria.push_back(IO_ACESS);
          break;
        default:
          cerr << "> ERRO: Tipo de acesso inválido: " << get<1>(i) << endl;
      }

      listaRequisicoes.push_back(endMemoria);
    }
  }

  // PROCESSOS CARREGADOS
  cout << ">> Processos carregados: " << listaDeProcessos.size() << "\n>>" ;
  for (int i = 0; i < listaDeProcessos.size(); i++) {
    cout << " P" << listaDeProcessos[i]->idProcesso << ";";
  } cout << "\n\n"; 

  // REQUISIÇÕES CARREGADAS
  cout << ">> Requisições carregadas: " << listaRequisicoes.size() << endl;

  qtdQuadros = qtdQuadrosMemPrincipal/listaDeProcessos.size();
  cout << ">> Sincronizando memória virtual" << endl;
  for(int i = 0; i < listaDeProcessos.size(); i++) {
    for (int j = 0; j < qtdQuadros; j++) {
      listaDeProcessos[i]->tabelaPaginas[j]->bitAlocacaoMemoria = 1;
    }
    memoriaVirtual.push_back(listaDeProcessos[i]->tabelaPaginas);
  }
  cout << "> Memória Virtual inicializada!" << endl;
  cout << "> Tamanho: " << memoriaVirtual.size()<< endl;

  cout << ">> Sincronizando a quantidade de quadros para cada processo na Memória Principal" << endl;
  cout << "> Quantidade padrão de quadros por processo: " << qtdQuadros << endl;
  for(int i = 0; i < listaDeProcessos.size(); i++) {
    deque<Pagina*> quadros;

    // Insere a memória virtual em todos os quadros
    for(int j = 0; j < qtdQuadros; j++) {
        quadros.push_back(memoriaVirtual[i][j]);
    }

    // Inserção dos quadros na memória principal
    memoriaPrincipal.push_back(quadros);
    cout << "> " << quadros.size() << " quadros inseridos na memória principal!" << endl;
    quadros.clear();
  }
  cout << "> Memória principal populada!" << endl;
  cout << "> Tamanho: " << memoriaPrincipal.size()<< "\n\n";

  if (ALGO == "LRU") {
    LRU(TAM_PAG, qtdQuadros);
    cout << "Swaps de página: " << qtdSwapsPaginas << endl;
    cout << "Faltas de página: " << qtdFaltaPag << endl;
  } else {
    Relogio(TAM_PAG, qtdQuadros);
    cout << "Swaps de página: " << qtdSwapsPaginas << endl;
    cout << "Faltas de página: " << qtdFaltaPag << endl;
  }
}
