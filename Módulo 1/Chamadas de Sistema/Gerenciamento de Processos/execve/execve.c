
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
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main (void) {
	int e;
	char *envp[] = {NULL};
	char *argv[] = {"/bin/echo", "Esse é um echo executado com execve", NULL};

	e = execve("/bin/echo", argv, envp);
	if (e == -1)
		fprintf(stderr, "ERROR: %s\n", strerror(errno));
	return 0;
}