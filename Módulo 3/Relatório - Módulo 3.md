# Módulo 2

Disciplina: SSC5723 - Sistemas Operacionais
Grupo: gspso3 - 2020
Repositório Github: https://github.com/rogerscristo/SSC5723-gpso3
Alunos: 
- Rogers Silva de Cristo - 10355930
- Cairo Mateus Neves Ribeiro - 11925833
___
## 1.  Visão geral
Neste módulo, o simulador requisitado deve ser capaz de gerenciar o uso da memória principal, bem como a alocação de páginas na memória virtual. As instruções de criação (C), leitura (R), escrita (W), envio para CPU (P) e requisição de E/S (I) são obtidas pelo arquivo de entrada:

(input.txt neste repositório)
```
P1 C 500
P1 R (0)2
P1 R (1024)2
P1 P  (1)2
P1 R (2)2
P1 P (2)2
P1 W  (1024)2
P7 C 1000
P7 R (4095)2
P7 R  (800)2
P7 I  (2)2
P7 R (801)2
P7 W  (4096)2
P1 R (3)2
P1 R  (4)2
P1 W (1025)2
P1 W  (1026)2
```

Algumas estruturas de dados foram adotadas para estre trabalhos, tais como vetores, deques e mapas. Para solucionar o problema de paginação dois algoritmos de substituição de páginas foram escolhidos: LRU e Relógio. Estes tópicos são discutidos com maior nível de detalhe nos tópicos seguintes.

## 2. Classes e estruturas de dados
### 2.1 Páginas
Neste trabalho tratamos as páginas como uma classe `Pagina`. Nesta, são definidos alguns argumentos que vão de encontro com os requisitos deste trabalho, incluindo o ID do processo pai dessa página, o ID único da página e um bit que indica a alocação desta página em memória (ou não). A memória principal é composta por um deque de deques de `Pagina`, facilitando assim a remoção nos dois extremos da estrutura de dados, necessário para alguns algoritmos.

### 2.2 Processos
Similarmente, os processos são definidos pela classe `Processo`. Seus argumentos são: ID único do processo, tamanho e um vetor de `Pagina` com tamamnho parametrizável, o qual representa a tabela de páginas.

### 2.3 Estruturas de dados
Ambas as classes são usadas para criação de uma memória principal (como descrito anteriormente), uma memória virtual (vetor de vetores de `Pagina`) e uma lista de processo (vetor de `Processo`). Complementarmente, algumas variáveis globais são igualmente criadas para auxiliar nos processos de leitura de entrada e impressão na tela.


## 3. Implementação LRU
Como explicitado pelo próprio nome, neste algoritmo uma página que é utizada menos frequentemente é substituída quando há a necessidade. Neste trabalho o LRU foi implementado seguindo os seguintes passos:

- Percorre o vetor de requisições (e.g. R, W, P e I) e, para cada um, realiza sua operação correspondente.
    - Caso haja falta de página, imprime na tela uma mensagem e incrementa o contador de faltas de páginas. Após isso, continua a execução normalmente.
    - Caso o tipo de acesso seja P ou I, imprime na tela a descrição da requisição e continua a execução para as requisições seguintes.
    - Nos casos dos tipos de acesso R ou W, o algoritmo inicia a execução propriamente dita do LRU:
        - Verificar se a página requisitada já existe na memória.
            - Se a página não estiver em memória e houver espaço livre, carrega a página diretamente na memória.
            - Se a página não estiver em memória e NÃO houver espaço livre, faz o swap de páginas usando a estrutura de deque e incrementa o contador de swaps.
            - Se a página já estiver em memória, utiliza um marcador para indicar o uso recente desse endereço de memória, acionando um break na sequência.
        - Por fim, apaga o endereço usado menos recentemente da memória e insere a página requisitada.

Todos os passos do algoritmo são retornados em um log na tela, facilitando o acompanhamento da execução.
        

## 4. Implementação Relógio
Os quadros de página são organizados em torno de uma lista circular no formato de um relógio, onde o relógio aponta para a página mais antiga.

No algoritmo do relógio se o bit R foi igual a zero o quadro de página é selecionado para a substituição de página. O próximo quadro de página é selecionado e é então verificado o bit R. Caso a lista seja percorrida e voltar ao quadro de página inicial esse quadro é selecionado para remoção por ser o mais antigo.

O algoritmo foi implementado da seguinte forma:

- Percorre o vetor de requisições (e.g. R, W, P e I) e, para cada um, realiza sua operação correspondente.
    - Caso haja falta de página, imprime na tela uma mensagem e incrementa o contador de faltas de páginas. Após isso, continua a execução normalmente.
    - Caso o tipo de acesso seja P ou I, imprime na tela a descrição da requisição e continua a execução para as requisições seguintes.
    - Nos casos dos tipos de acesso R ou W, o algoritmo inicia a execução propriamente dita do relógio:
        - Enquanto o quadro de página não for encontrado executa o loop.
        - Se o bit de referência for igual a 0, então a página é selecionada para substituição de página.
        - Se não, muda para a próxima página e verifica se essa é a página final.
        - Esse processo é realizado até encontrar a página para substituição.

Todos os passos do algoritmo são retornados em um log na tela, facilitando o acompanhamento da execução.
