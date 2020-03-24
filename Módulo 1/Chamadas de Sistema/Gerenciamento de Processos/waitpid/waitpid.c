
/*******************************************************************
*
Disciplina: SSC5723 - Sistemas Operacionais
Grupo: gspso3 - 2020
Repositório Github: https://github.com/rogerscristo/SSC5723-gpso3
Alunos: Rogers Silva de Cristo          10355930
        Cairo Mateus Neves Ribeiro      11925833
*
******************************************************************/

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main (void) {
	const int NPROCS = 3; // 3 processos são iniciados
	int childpid;
	int i;
	int wait_vector[NPROCS];
	int status[NPROCS];


	pid_t id_proceso = getpid();
	printf("Processo pai com PID: %d\n\n", id_proceso);


	// Criação dos processos filhos
	for (i=0; i < NPROCS; i++) {
		if ((childpid = fork()) == -1) {
			fprintf(stderr, "Não foi possível criar o filho %d: %s\n", i, strerror(errno));
			exit(-1);
		}

		wait_vector[i] = childpid; // Cada processo filho é adicionado ao vetor de espera

		if (childpid == 0) {
			pid_t id_proceso = getpid();
			printf("Criou o processo filho com PID: %d\n", id_proceso);
			i = NPROCS; // Evita que processos filhos criem outros filhos
		}
	}


	// Usa o waitpid para aguardar a finalização dos processos filhos
	if (childpid > 0) { // Se o processo for pai
		for (i = 0; i < NPROCS; i++) {
		 	waitpid(wait_vector[i], &status[i], 0);

		 	// Detecção de erros
		 	if (WIFEXITED(status[i]) == 0) {
				printf("ERROR: O processo %d não terminou corretamente\n", wait_vector[i]);
			}else {
			 	printf("\nFinalizou o processo filho com PID: %d\n", wait_vector[i]);
				printf("Restam %d processos filhos ativos\n", NPROCS - i - 1);
			}
		}
	}
}