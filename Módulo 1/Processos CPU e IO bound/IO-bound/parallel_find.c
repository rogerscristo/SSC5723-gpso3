
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

int main() {
    int status = system("dd if=/dev/zero of=/tmp/dd.test bs=4M count=1000");
    return 0;
}