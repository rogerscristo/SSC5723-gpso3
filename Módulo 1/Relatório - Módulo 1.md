# Módulo 1

Disciplina: SSC5723 - Sistemas Operacionais
Grupo: gspso3 - 2020
Repositório Github: https://github.com/rogerscristo/SSC5723-gpso3
Alunos: 
- Rogers Silva de Cristo - 10355930
- Cairo Mateus Neves Ribeiro - 11925833
___
## 1.  Chamadas de sistema
 Cada grupo deverá selecionar pelo menos 3 primitivas de chamada de sistema disponíveis no Linux, para cada uma das categorias (gerenciamento de memória, processos, E/S e arquivos), totalizando 9 primitivas a serem analisadas. Deverão ser construídos programas para exemplificar a utilização de cada uma das primitivas escolhidas.  

### 1.1 Análise das system calls apresentadas pelo `strace`
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

### 1.2 Gerenciamento de processos
Nesta etapa decidimos por implementar e analisar três chamadas de sistema: `fork`, `waitpid` e `execve`. Para acessar o código de cada uma das três entre em [https://github.com/rogerscristo/SSC5723-gpso3/tree/master/M%C3%B3dulo%201/Chamadas%20de%20Sistema/Gerenciamento%20de%20Processos/](https://github.com/rogerscristo/SSC5723-gpso3/tree/master/M%C3%B3dulo%201/Chamadas%20de%20Sistema/Gerenciamento%20de%20Processos/)

#### 1.2.1	fork
A chamada `fork` cria uma duplicata do processo atual. O processo criado a partir do `fork` é chamado processo filho, enquanto o processo do qual o `fork` é chamado é denominado processo pai. É importante notar que apesar de ambos os processos serem identicos, estes são executados em espaços distintos de memória e possuem PIDs diferentes.

O código implementado para utilização do `fork` nesse projeto pode ser acessado em [https://github.com/rogerscristo/SSC5723-gpso3/blob/master/M%C3%B3dulo%201/Chamadas%20de%20Sistema/Gerenciamento%20de%20Processos/fork/fork.c](https://github.com/rogerscristo/SSC5723-gpso3/blob/master/M%C3%B3dulo%201/Chamadas%20de%20Sistema/Gerenciamento%20de%20Processos/fork/fork.c). Para realizar a análise utilizando o `strace` o seguinte comando foi executado:

    strace -o strace_fork_dump -C ./fork.o

A flag `-C` permite a obtenção do relatório adicional no qual são apresentados os tempos de execução (em segundos) de cada chamada de sistema.

O retorno do strace para o código desenvolvido é apresentado abaixo:

    execve("./fork.o", ["./fork.o"], 0x7ffdd9d11f28 /* 78 vars */) = 0
    brk(NULL)                               = 0x55db2b2c5000
    access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
    access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
    fstat(3, {st_mode=S_IFREG|0644, st_size=95204, ...}) = 0
    mmap(NULL, 95204, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fad8901d000
    close(3)                                = 0
    access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
    read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260\34\2\0\0\0\0\0"..., 832) = 832
    fstat(3, {st_mode=S_IFREG|0755, st_size=2030544, ...}) = 0
    mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fad8901b000
    mmap(NULL, 4131552, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fad88a1d000
    mprotect(0x7fad88c04000, 2097152, PROT_NONE) = 0
    mmap(0x7fad88e04000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7fad88e04000
    mmap(0x7fad88e0a000, 15072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fad88e0a000
    close(3)                                = 0
    arch_prctl(ARCH_SET_FS, 0x7fad8901c4c0) = 0
    mprotect(0x7fad88e04000, 16384, PROT_READ) = 0
    mprotect(0x55db2af80000, 4096, PROT_READ) = 0
    mprotect(0x7fad89035000, 4096, PROT_READ) = 0
    munmap(0x7fad8901d000, 95204)           = 0
    clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7fad8901c790) = 31927
    getpid()                                = 31926
    fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
    brk(NULL)                               = 0x55db2b2c5000
    brk(0x55db2b2e6000)                     = 0x55db2b2e6000
    write(1, "PID do processo pai: 31926\n", 27) = ? ERESTARTSYS (To be restarted if SA_RESTART is set)
    --- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=31927, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
    write(1, "PID do processo pai: 31926\n", 27) = 27
    exit_group(0)                           = ?
    +++ exited with 0 +++
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
    18.55    0.000146          29         5           mmap
    17.03    0.000134         134         1           clone
    13.21    0.000104          35         3         3 access
    10.29    0.000081          81         1           execve
    9.91    0.000078          20         4           mprotect
    6.48    0.000051          26         2           openat
    5.97    0.000047          47         1           munmap
    4.07    0.000032          11         3           brk
    3.81    0.000030          10         3           fstat
    3.30    0.000026          13         2           close
    3.05    0.000024          24         1           getpid
    1.65    0.000013          13         1           read
    1.65    0.000013          13         1           write
    1.02    0.000008           8         1           arch_prctl
    ------ ----------- ----------- --------- --------- ----------------
    100.00    0.000787                    29         3 total


A rotina se inicia pela chamada `execve`, a qual executa o programa fork.o. Na sequência `brk(NULL)` é chamado com o argumento `NULL` indicando que não houve alocação de memória (`malloc`) no código. Duas chamadas `access` são introduzidas para verificar as permissões dos arquivos `ld.so.nohwcap` e `ld.so.preload`, os quais não existem no sistema utilizado (Ubuntu 18.04 LTS). Seguindo, `openat` é utilizado para abrir o arquivo `ld.so.cache`, retornando o descritor de arquivo 3 e, em série, a chamada `fstat`obtém o status do arquivo 3, enquando `nmap` aloca o mesmo arquivo no endereço de memória `0x7fad8901d000` para, por fim, a chamada `close` fechar o arquivo. Um processo similar é utilizado para o arquivo `libc.so.6`, com a diferença de que chamadas adicionais `nmap` são adicionadas, além de uma chamada `mprotect`, a qual é utilizada para proteger a região de memória `0x7fad88c04000`.  Após fechar o último arquivo, `arch_prctl`é utilizado para definir a arquitetura do processo como 64-bits (`ARCH_SET_FS`). Continuando, três chamadas `mprotect` são utilizadas para proteger para leitura os endereços de memória respectivos aos arquivos abertos anteriormente. Uma chamada `munmap` é escolhida para desmapear o endereço `0x7fad8901d000` da memória (respectivo ao arquivo `ld.so.cache`). Finalmente, a chamada `clone` é acionada, respectiva ao `fork` utilizado no código `fork.c`, no qual o processo pai 31926 é clonado, obtendo-se o processo filho 31927. O `brk` sequente define o endereço final de memória do processo filho. As chamadas `write` na sequência são executadas para execução do dois `printf` presentes no código `fork.c`. Por fim, a chamada `exit_group(0) ` é executada para terminar a execução dos processos. O restante do log se refere ao tempo de execução de cada chamada.

Salienta-se que em momento algum a chamada `fork` é demonstrada no log do `strace`. Isso se deve ao fato de que o `fork` utilizado em linguagem C chama a biblioteca `glibc`, que por sua vez implementa o `fork` como um wrapper da chamada de sistema `clone`. Para uma explicação mais detalhada consulte os dois seguintes links:

 - [https://thorstenball.com/blog/2014/06/13/where-did-fork-go/](https://thorstenball.com/blog/2014/06/13/where-did-fork-go/)
 - [https://stackoverflow.com/questions/18904292/is-it-true-that-fork-calls-clone-internally](https://stackoverflow.com/questions/18904292/is-it-true-that-fork-calls-clone-internally)

#### 1.2.2	waitpid
TODO: Fazer descrição similar a da seção fork

#### 1.2.3	execve
TODO: Fazer descrição similar a da seção fork

### 1.3 Gerenciamento de arquivos
TODO: Fazer descrição similar a da seção Gerenciamento de processos

#### 1.3.1	stat
TODO: Fazer descrição similar a da seção fork

### 1.4 Gerenciamento de memória
TODO: Fazer descrição similar a da seção Gerenciamento de processos