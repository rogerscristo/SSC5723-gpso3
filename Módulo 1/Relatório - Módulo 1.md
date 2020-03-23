# Módulo 1

Disciplina: SSC5723 - Sistemas Operacionais

Grupo: gspso3 - 2020

Repositório Github: https://github.com/rogerscristo/SSC5723-gpso3

Alunos: 
- Rogers Silva de Cristo - 10355930
- Cairo Mateus Neves Ribeiro - 11925833
___
## Atividade 1 - Chamadas de sistema
 Cada grupo deverá selecionar pelo menos 3 primitivas de chamada de sistema disponíveis no Linux, para cada uma das categorias (gerenciamento de memória, processos, E/S e arquivos), totalizando 9 primitivas a serem analisadas. Deverão ser construídos programas para exemplificar a utilização de cada uma das primitivas escolhidas.  

### Análise das system calls apresentadas pelo `strace`
Um breve descrição de cada system call do `strace` é apresentada abaixo, de modo a facilitar o entendimento e análise do log retornado para cada system call utilizada nesse módulo.

|syscall|descrição  |
|--|--|
| read | lê bytes de um descritor de arquivos (file, socket) |
| write | escreve bytes de um descritor de arquivo (file, socket) |
| open | abre um arquivo (retorna um descritor de arquivo) |
| close | fecha um descritor de arquivo |
| fork | cria um novo processo (processo atual é clonado) |
| exec | executa um novo programa |
| connect | conecta a um host na rede |
| accept | aceita uma conexão de rede |
| stat | lê as estatísticas de um arquivo |
| ioctl | define as propriedades de E/S, ou outras funções diversas |
| nmap | mapeia um arquivo para um endereço de memória respectivo a um processo |
| brk | extende o ponteiro para a heap |



