#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define KILOBYTE 1024
#define MEGABYTE 1048576
#define TOTAL_ARQUIVOS 7
#define TOTAL_ITERACOES 10

void save_csv(char *nome_arquivo, double *logs_criacao, double *logs_leitura, double *logs_remocao);
double calcular_tempo_em_segundos(clock_t, clock_t);
double cria_arquivo(int tamArquivo, char *nomeArquivo);
double le_arquivo(char *nomeArquivo);
double remove_arquivo(char *nomeArquivo);

int main (int argc, char argv[]) {
	char *nomeArquivo[] = { "5KB.csv", "10KB.csv", "100KB.csv", "1MB.csv", "10MB.csv", "100MB.csv", "500MB.csv" };
	int tamArquivos[TOTAL_ARQUIVOS] = { KILOBYTE * 5, KILOBYTE * 10, KILOBYTE * 100, MEGABYTE, MEGABYTE * 10, MEGABYTE * 100, MEGABYTE * 500 };

	printf("==== Total de iterações %d\n", TOTAL_ITERACOES);
	char nome[(int)(floor(log10(TOTAL_ITERACOES) + 1))]; //Cria string para armazenamento do nome do arquivo

	for (int i = 0; i < TOTAL_ARQUIVOS; i++) {
		printf("=== Operações para arquivo %s\n", nomeArquivo[i]);

		printf("== Criando arquivos\n");
		double logs_criacao[TOTAL_ITERACOES];
		for (int j = 0; j < TOTAL_ITERACOES; j++) {
			sprintf(nome, "%d", j);
			//char *caminho = strcat(caminho_pendrive, nome);
			logs_criacao[j] = cria_arquivo(tamArquivos[i], nome);
		}
		
		printf("== Lendo arquivos\n");
		double logs_leitura[TOTAL_ITERACOES];
		for (int j = 0; j < TOTAL_ITERACOES; j++) {
			sprintf(nome, "%d", j);
			//char *caminho = strcat(caminho_pendrive, nome);
			logs_leitura[j] = le_arquivo(nome);
		}

		printf("== Removendo arquivos\n");
		double logs_remocao[TOTAL_ITERACOES];
		for (int j = 0; j < TOTAL_ITERACOES; j++) {
			sprintf(nome, "%d", j);
			//char *caminho = strcat(caminho_pendrive, nome);
			logs_remocao[j] = remove_arquivo(nome);
		}

		//char *caminho = strcat(tipo_particao, nomeArquivo[i]);
		printf("== Salvando arquivo de log\n");
		save_csv(nomeArquivo[i], logs_criacao, logs_leitura, logs_remocao);
		printf("== Experimento concluído!\n\n");
	}

	return EXIT_SUCCESS;
}

void save_csv(char *nome_arquivo, double *logs_criacao, double *logs_leitura, double *logs_remocao) {
	FILE *fp = fopen(nome_arquivo, "w");

	fprintf(fp, "operacao;tempo\n");

	for (int i = 0; i < TOTAL_ITERACOES; i++) {
		fprintf(fp, "criacao;%.7f\n", logs_criacao[i]);
	}

	for (int i = 0; i < TOTAL_ITERACOES; i++) {
		fprintf(fp, "leitura;%.7f\n", logs_leitura[i]);
	}

	for (int i = 0; i < TOTAL_ITERACOES; i++) {
		fprintf(fp, "remocao;%.7f\n", logs_remocao[i]);
	}
	fclose(fp);	
}


double calcular_tempo_em_segundos(clock_t tempo_inico, clock_t tempo_fim) {
	return (double)((double) (tempo_fim - tempo_inico) / CLOCKS_PER_SEC);
}

double cria_arquivo(int tamArquivo, char *nomeArquivo) {
	FILE *fp;
	clock_t tempo_inicio, tempo_fim;
	double tempoExecucao;

	tempo_inicio = clock();
	fp = fopen(nomeArquivo, "w");
	fseek(fp, tamArquivo, SEEK_SET);
	fputc('\0', fp);
	fclose(fp);
	tempo_fim = clock();
	tempoExecucao = calcular_tempo_em_segundos(tempo_inicio, tempo_fim);
	//printf("Tempo execução (criacao): %f\n", tempoExecucao);
	return tempoExecucao;
}

double le_arquivo(char *nomeArquivo) {
	FILE *fp;
	clock_t tempo_inicio, tempo_fim;
	double tempoExecucao;
	char buffer[KILOBYTE];

	tempo_inicio = clock();
	fp = fopen(nomeArquivo, "r");
	while (fgets(buffer, KILOBYTE, fp) != NULL);
	fclose(fp);
	tempo_fim = clock();
	tempoExecucao = calcular_tempo_em_segundos(tempo_inicio, tempo_fim);

	return tempoExecucao;
}

double remove_arquivo(char *nomeArquivo) {
	clock_t tempo_inicio, tempo_fim;
	double tempoExecucao;

	tempo_inicio = clock();
	remove(nomeArquivo);
	tempo_fim = clock();
	tempoExecucao = calcular_tempo_em_segundos(tempo_inicio, tempo_fim);

	return tempoExecucao;
}
