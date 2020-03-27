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
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) {
    struct rlimit *limiteMemoria = malloc(sizeof(struct rlimit));
    getrlimit(RLIMIT_MEMLOCK, limiteMemoria);
    printf("Limite de memoria disponivel: %ld\n", limiteMemoria->rlim_max);

    struct rlimit *limiteCpu = malloc(sizeof(struct rlimit));
    int statusCPU = getrlimit(RLIMIT_DATA, limiteCpu);
    printf("Tamanho máximo segmentos processo: %ld\n", limiteCpu->rlim_max);

    return EXIT_SUCCESS;
}