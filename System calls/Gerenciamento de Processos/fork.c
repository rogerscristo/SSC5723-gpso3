/*******************************************************************
*
Disciplina: SSC5723 - Sistemas Operacionais
Grupo: gspso3 - 2020
Repositório Github: https://github.com/rogerscristo/SSC5723-gpso3
Alunos: Rogers Silva de Cristo          10355930
        Cairo Mateus Neves Ribeiro      11925833
*
******************************************************************/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    int i;
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        //O código aqui dentro será executado no processo filho
        printf("PID do processo filho: %d\n", getpid());
    }
    else {
        //O código neste trecho será executado no processo pai
        printf("PID do processo pai: %d\n", getpid());
    }

    return 0;
}	