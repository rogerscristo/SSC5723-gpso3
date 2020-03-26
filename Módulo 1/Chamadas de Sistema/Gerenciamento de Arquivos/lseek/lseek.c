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
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void main(int argc, char *argv[]) {
    char *pathArquivo = "./arquivo.txt";
    int file = open(pathArquivo, O_RDWR | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG);
    int posicaoPonteiro = lseek(file, 0L, SEEK_SET);

    if (posicaoPonteiro == -1) {
        fprintf(stderr, "ERROR: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    close(file);
    return EXIT_SUCCESS;
}
