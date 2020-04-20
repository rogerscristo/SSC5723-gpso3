#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TRUE 1 // Define a variavel TRUE
#define FALSE 0 // Define a variável FALSE
#define MAX 10000000 // Tamanho do buffer.

pthread_mutex_t mutex; // Cria a variável de controle.
pthread_cond_t full; // Cria a variável que representa o buffer cheio.
pthread_cond_t empty; // Cria a variável que representa o buffer vazio.
unsigned int buffer = 0;

/**
 * Define a função do produtor.
 */
void *produtor(void *ponteiro) {
    int item, i;

    for(i = 1; i <= MAX; i++) {
        pthread_mutex_lock(&mutex);

        while(buffer != 0) {
            pthread_cond_wait(&empty, &mutex);
        }

        buffer = i;
        printf("%d\n", buffer);

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(EXIT_SUCCESS);
}

/**
 * Define a função do consumidor.
 */
void *consumidor(void *ponteiro) {
    int item, i;

    for(i = 1; i <= MAX; i++) {
        pthread_mutex_lock(&mutex);

        while(buffer == 0) {
            pthread_cond_wait(&full, &mutex);
        }

        buffer = 0;
        printf("%d\n", buffer);

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }

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
