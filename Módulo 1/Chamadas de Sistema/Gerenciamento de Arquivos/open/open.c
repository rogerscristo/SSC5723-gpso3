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
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void main(int argc, char *argv[]) {
    char *pathArquivo = "./arquivo.txt";
    int file = open(pathArquivo, O_RDWR | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG);

    if (file == -1) {
		fprintf(stderr, "ERROR: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
