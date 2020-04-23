/*******************************************************************
*
Disciplina: SSC5723 - Sistemas Operacionais
Grupo: gspso3 - 2020
Repositório Github: https://github.com/rogerscristo/SSC5723-gpso3
Alunos: Rogers Silva de Cristo          10355930
        Cairo Mateus Neves Ribeiro      11925833
*
******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TRUE 1 // Define a variavel TRUE
#define FALSE 0 // Define a variável FALSE
#define MAX 3 // Tamanho máximo do buffer.

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Cria a variável de controle do mutex.
pthread_cond_t full = PTHREAD_COND_INITIALIZER; // Cria a variável que representa o buffer cheio.
pthread_cond_t empty = PTHREAD_COND_INITIALIZER; // Cria a variável que representa o buffer vazio.
unsigned int buffer[MAX]; // Instanciamento do buffer
unsigned int insert_pos = 0; // Variável para controle da posição de inserção no buffer
unsigned int remove_pos = 0; // Variável para controle da posição de remoção no buffer
unsigned int num_elem = 0; // Variável para controle da ocupação atual do buffer

/*
    Define a função do produtor.
*/
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

/*
    Define a função do consumidor.
*/
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

