# Módulo 2

Disciplina: SSC5723 - Sistemas Operacionais
Grupo: gspso3 - 2020
Repositório Github: https://github.com/rogerscristo/SSC5723-gpso3
Alunos: 
- Rogers Silva de Cristo - 10355930
- Cairo Mateus Neves Ribeiro - 11925833
___
## 1.  Produtor Consumidor
O problema do Produtor e o Consumidor consiste em um conjunto de processos que compartilham um mesmo buffer. Os processos chamados produtores colocam informação no buffer. Os processos chamados consumidores retiram informação deste buffer. 

Trata-se de um problema clássico em sistemas operacionais, que busca exemplificar de forma clara, situações de impasses que ocorrem no gerenciamento de processos de um sistema operacional. É preciso se preocupar com acessos indevidos a certos recursos que são compartilhados entre os processos, e manter sincronismo entre os mesmos. 

Para controlarmos o acesso a essas variáveis e garantir o sincronismo nas operações, vamos utilizar semáforos. Em ciência da computação, semáforo é uma variável especial protegida (ou tipo abstrato de dados) que tem como função o controle de acesso a recursos compartilhados (por exemplo, um espaço de armazenamento) num ambiente multitarefa. Com as variáveis do tipo pthread_mutex_t da biblioteca pthreads - Posix, podemos controlar esses dados com toda segurança. 


Outro controle importante é a demanda de processamento, espera ociosa, que o programa irá gerar, pois quando um processo não está liberado para gravar ou ler, deve entrar em estado de espera para não consumir processamento, e deve ser avisado quando pode voltar a processar.

**O Problema**
- O produtor insere em uma região: Ainda não houve consumo
- O consumidor remove de uma região: Já foi consumida
- Espera ociosa X Escalonamento do processo X Uso CPU

**A Solução**
- Utilizar Exclusão mutua (semáforos)
- Eliminar a espera ociosa:
- Dormir (dow) /acordar (up) X Semáforos full/empty
- Mutex (Mutual exclusion)

**Requisitos da Solução**

- O programa deve ter um buffer limitado, acessível a qualquer processo decorrente do processo principal;
- O programa deve ter uma fila apontando para o próximo endereço livre, a ser escrito;
- O programa deve ter uma fila apontando para o próximo endereço ocupado, a ser lido e liberado;
- O programa deve controlar as seções críticas (Compartilhamento de memória), para que não haja acessos indevidos.
- O programa deve ter a capacidade de colocar um processo em modo de espera;
- O programa deve ter a capacidade de controlar quando um processo está em espera, para poder "chamar" o mesmo;
- O programa deve controlar quantos endereços estão livres e quantos endereços estão ocupados.


**Recursos para desenvolver a solução**

A solução do problema deve utilizar a biblioteca pthreads, a qual possibilita a programação de forma concorrente com as funções de: controle de threads, criação de threads, suspensão de threads, execução e controle de exclusão mútua por semáforos binários, para controle da seção crítica. 



**Site para consulta**

http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html


### 1.1 Execução
O código implementado nesse módulo pode ser encontrado em: https://github.com/rogerscristo/SSC5723-gpso3/tree/master/M%C3%B3dulo%202

Para sua compilação, execute:
```bash
make all
```

Para executar o código, execute:
```bash
./prod_consumidor.o
```

### 1.2 Implementação da solução produtor/consumidor
O código que atende aos requisitos definidos nesse módulo foi escrito em linguagem `C` e utiliza a biblioteca `pthreads` para programação concorrente. Conforme apontado na especificação, utilizamos um semáforo binário para sincronização das threads.


Foram definidas três macros, respectivas a valores booleanos True e False, bem como o tamanho máximo do buffer.
Apesar de utilizar somente 3 posições no buffer, o código é capaz de executar qualquer buffer de __n__ posições.

```c
#define TRUE 1
#define FALSE 0
#define MAX 3
```

Na sequência, são instanciadas diversas variáveis necessárias para implementação da solução. Seus usos são apresentados nos comentários do código abaixo:

```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Cria a variável de controle do mutex.
pthread_cond_t full = PTHREAD_COND_INITIALIZER; // Cria a variável que representa o buffer cheio.
pthread_cond_t empty = PTHREAD_COND_INITIALIZER; // Cria a variável que representa o buffer vazio.
unsigned int buffer[MAX]; // Instanciamento do buffer
unsigned int insert_pos = 0; // Variável para controle da posição de inserção no buffer
unsigned int remove_pos = 0; // Variável para controle da posição de remoção no buffer
unsigned int num_elem = 0; // Variável para controle da ocupação atual do buffer
```

A função que implementa o produtor é apresentada abaixo. Nota-se a utilização do mutex para regular a sincronização desse método, bem como as condições de operação quando o buffer é preenchido completamente. Os elementos inseridos no buffer são simplesmente os índices inteiros correspondentes a cada interação do produtor no buffer.
```c
void *produtor(void *ponteiro) {
    printf("Inicializando rotina de produção...\n");
    printf("--- Ocupação atual do buffer: %d/%d\n", num_elem, MAX);

    for(int i = 1; i <= MAX; i++) {
        pthread_mutex_lock(&mutex);

        // Bloqueia a thread produtor caso o buffer esteja cheio
        while(num_elem == MAX) {
            pthread_cond_wait(&empty, &mutex);
        }

        buffer[insert_pos] = i; // Insere o índice i na posição insert_pos do buffer
        insert_pos = (insert_pos + 1) % MAX; // Reseta insert_pos para 0 quando insert_pos == MAX
        num_elem++;
        printf("--- Produtor: inseriu %d no buffer\tBuffer %d/%d\n", i, num_elem, MAX);

        pthread_cond_signal(&full); 
        pthread_mutex_unlock(&mutex);
    }
    printf("Finalizando rotina de produção...\n");

    pthread_exit(EXIT_SUCCESS);
}
```

Similarmente ao produtor, o consumidor também faz uso do mutex para sincronizar sua execução, embora sua sinalização de parada aconteça quando o buffer está vazio. O valor atual da posição a ser removida é salvo na variável `payload`, enquanto a remoção completa de um elemento do buffer é indicada pela sua instanciação em 0.
```c
void *consumidor(void *ponteiro) {
    printf("Inicializando rotina de consumo...\n");
    printf("--- Ocupação atual do buffer: %d/%d\n", num_elem, MAX);

    for(int i = 1; i <= MAX; i++) {
        pthread_mutex_lock(&mutex);

        // Bloqueia o consumidor caso o buffer esteja vazio
        while(num_elem == 0) {
            pthread_cond_wait(&full, &mutex);
        }

        int payload = buffer[remove_pos]; // "Remove" do buffer o elemento na posição remove_pos e salva em payload
        buffer[remove_pos] = 0;
        printf("--- Consumidor: removeu %d da posição %d do buffer\tBuffer %d/%d\n", payload, remove_pos, num_elem, MAX);
        remove_pos = (remove_pos + 1) % MAX; // Reseta remove_post para 0 quando remove_pos == MAX
        num_elem--;

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }

    printf("Finalizando rotina de consumo...\n");

    pthread_exit(EXIT_SUCCESS);
}
```

Por fim, o código de `main` é apresentado. Nele implementamos a criação das threads para o produtor e o consumidor, bem como a instanciação das variáveis de controle e a chamada `join` para cada thread.
```c
int main(int argc, char **argv) {
    pthread_t thread01, thread02; // Cria duas threads

    pthread_mutex_init(&mutex, 0); // Inicializa o mutex em 0

    // Inicializa as variáveis empty e full em 0
    pthread_cond_init(&empty, 0);
    pthread_cond_init(&full, 0);

    pthread_create(&thread02, NULL, consumidor, 0); // thread02 é o consumidor
    pthread_create(&thread01, NULL, produtor, 0); // thread01 é o produtor'
    pthread_join(thread02, 0); // Aguarda o término do consumidor
    pthread_join(thread01, 0); // Aguarda o término do produtor

    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("--- Ocupação atual do buffer: %d/%d\n", num_elem, MAX);

    return EXIT_SUCCESS;
}
```