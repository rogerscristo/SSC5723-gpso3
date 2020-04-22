#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TRUE 1 // Define a variavel TRUE
#define FALSE 0 // Define a variável FALSE
#define MAX 3 // Tamanho do buffer.

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Cria a variável de controle.
pthread_cond_t full = PTHREAD_COND_INITIALIZER; // Cria a variável que representa o buffer cheio.
pthread_cond_t empty = PTHREAD_COND_INITIALIZER; // Cria a variável que representa o buffer vazio.
unsigned int buffer[MAX];
unsigned int insert_pos = 0;
unsigned int remove_pos = 0;
unsigned int num_elem = 0;

/**
 * Define a função do produtor.
 */
void *produtor(void *ponteiro) {
    printf("Inicializando rotina de produção...\n");

    for(int i = 1; i <= MAX; i++) {
        pthread_mutex_lock(&mutex);

        while(num_elem == MAX) {
            pthread_cond_wait(&empty, &mutex);
        }

        buffer[insert_pos] = i;
        printf("Produtor: inseriu %d no buffer\n", i);

        insert_pos = (insert_pos + 1) % MAX; // Reseta insert_pos para 0 quando insert_pos == MAX
        num_elem++;

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }
    printf("Finalizando rotina de produção...\n");

    pthread_exit(EXIT_SUCCESS);
}

/**
 * Define a função do consumidor.
 */
void *consumidor(void *ponteiro) {
    printf("Inicializando rotina de consumo...\n");

    for(int i = 1; i <= MAX; i++) {
        pthread_mutex_lock(&mutex);

        while(num_elem == 0) {
            pthread_cond_wait(&full, &mutex);
        }

        int payload = buffer[remove_pos];
        printf("Consumidor: removeu %d da posição %d do buffer\n", buffer[remove_pos], remove_pos);

        remove_pos = (remove_pos + 1) % MAX;
        num_elem--;

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }

    printf("Finalizando rotina de consumo...\n");

    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    pthread_t thread01, thread02;

    pthread_mutex_init(&mutex, 0);

    pthread_cond_init(&empty, 0);
    pthread_cond_init(&full, 0);

    pthread_create(&thread02, NULL, consumidor, 0);
    pthread_create(&thread01, NULL, produtor, 0);
    pthread_join(thread02, 0);
    pthread_join(thread01, 0);

    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);

    pthread_mutex_destroy(&mutex);

    return EXIT_SUCCESS;
}
