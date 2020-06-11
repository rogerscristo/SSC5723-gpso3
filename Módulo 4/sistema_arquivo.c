#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KILOBYTE 1024
#define MEGABYTE 1048576
#define TOTAL_ARQUIVOS 7
#define TOTAL_ITERACOES 10

double calcular_tempo_em_segundos(clock_t, clock_t);

int main (int argc, char argv[]) {
	int i, j;
	FILE *fp;
	double tempoExecucao;
	char buffer[KILOBYTE];
	clock_t tempo_inicio, tempo_fim;
	char *nomeArquivo[] = { "ARQ_5KB", "ARQ_10KB", "ARQ_100KB", "ARQ_1MB", "ARQ_10MB", "ARQ_100MB", "ARQ_500MB" };
	int tamArquivos[TOTAL_ARQUIVOS] = { KILOBYTE * 5, KILOBYTE * 10, KILOBYTE * 100, MEGABYTE, MEGABYTE * 10, MEGABYTE * 100, MEGABYTE * 500 };
	
	for (j = 0; j < TOTAL_ITERACOES; j++) {
		for (i = 0; i < TOTAL_ARQUIVOS; i++) {
			// Cria o arquivo com o tamanho especificado.
			tempo_inicio = clock();
			fp = fopen(nomeArquivo[i], "w");
	    	fseek(fp, tamArquivos[i], SEEK_SET);
	    	fputc('\0', fp);
	    	fclose(fp);
	    	tempo_fim = clock();
			tempoExecucao = calcular_tempo_em_segundos(tempo_inicio, tempo_fim);
			printf("Tempo execução (criacao): %f\n", tempoExecucao);
	    	
	    	// Le os arquivos de acordo com a entrada.
	    	tempo_inicio = clock();
			fp = fopen(nomeArquivo[i], "r");
			while (fgets(buffer, KILOBYTE, fp) != NULL);
	    	fclose(fp);
	    	tempo_fim = clock();
	    	tempoExecucao = calcular_tempo_em_segundos(tempo_inicio, tempo_fim);
			printf("Tempo execução (leitura): %f\n", tempoExecucao);
			
	    	// Remove os arquivos.
	    	tempo_inicio = clock();
	    	remove(nomeArquivo[i]);
			tempo_fim = clock();
			tempoExecucao = calcular_tempo_em_segundos(tempo_inicio, tempo_fim);
			printf("Tempo execução (remocao): %f\n\n", tempoExecucao);
		}
	}
	
	return EXIT_SUCCESS;
}

double calcular_tempo_em_segundos(clock_t tempo_inico, clock_t tempo_fim) {
	return (double)((double) (tempo_fim - tempo_inico) / CLOCKS_PER_SEC);
}
