
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
  
int ackermann(int m, int n) { 
    if (m == 0){ 
        return n + 1; 
    } 
    else if((m > 0) && (n == 0)){ 
        return ackermann(m - 1, 1); 
    } 
    else if((m > 0) && (n > 0)){ 
        return ackermann(m - 1, ackermann(m, n - 1)); 
    } 
} 
  
int main() { 
    int A; 
    A = ackermann(4, 1); 
	printf("ackermann(4, 1) = %d\n", A);
    return 0; 
} 