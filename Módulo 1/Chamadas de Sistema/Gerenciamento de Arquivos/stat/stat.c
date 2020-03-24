
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
#include <sys/stat.h>

int main (void) {
	struct stat sfile; // Aponta para o struct do stat 
	stat("stat.c", &sfile); // Chamada de sistema do stat
	// Os printf abaixo acessam alguns campos do struct do stat referente ao arquivo stat.c
	printf("Stats do arquivo stats.c\n");
	printf("Permissões do arquivo: st_mode = %o\n", sfile.st_mode); 
	printf("ID do dispositivo no qual o arquivo stat.c reside: st_dev = %lu\n", sfile.st_dev); 
	printf("Tamanho do arquivo (bytes): st_size = %ld\n", sfile.st_size); 
	printf("Horário da última alteração no arquivo: st_mtime = %ld\n", sfile.st_mtime); 
	return 0;
}