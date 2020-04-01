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
Existem algumas situações nas quais pode ser necessário que um processo pai monitore possíveis mudanças de status em um determinado processo filho. A função `waitpid()` permite que um processo pai monitore o status de um filho específico. Por default, a função monitora apenas o status de `terminate`, porém demais status podem ser configurados via o argumento `options`.

O código implementado para utilização do `waitpid` nesse projeto pode ser acessado em https://github.com/rogerscristo/SSC5723-gpso3/blob/master/M%C3%B3dulo%201/Chamadas%20de%20Sistema/Gerenciamento%20de%20Processos/waitpid/waitpid.c. Para realizar a análise utilizando o `strace` o seguinte comando foi executado:

    strace -o strace_waitpid_dump -C ./waitpid.o

O retorno do strace para o código desenvolvido é apresentado abaixo:

    execve("./waitpid.o", ["./waitpid.o"], 0x7ffed0f67428 /* 73 vars */) = 0
    brk(NULL)                               = 0x5560f9a93000
    access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
    access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
    fstat(3, {st_mode=S_IFREG|0644, st_size=95204, ...}) = 0
    mmap(NULL, 95204, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fe284837000
    close(3)                                = 0
    access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
    read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260\34\2\0\0\0\0\0"..., 832) = 832
    fstat(3, {st_mode=S_IFREG|0755, st_size=2030544, ...}) = 0
    mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe284835000
    mmap(NULL, 4131552, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fe284237000
    mprotect(0x7fe28441e000, 2097152, PROT_NONE) = 0
    mmap(0x7fe28461e000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7fe28461e000
    mmap(0x7fe284624000, 15072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fe284624000
    close(3)                                = 0
    arch_prctl(ARCH_SET_FS, 0x7fe2848364c0) = 0
    mprotect(0x7fe28461e000, 16384, PROT_READ) = 0
    mprotect(0x5560f8799000, 4096, PROT_READ) = 0
    mprotect(0x7fe28484f000, 4096, PROT_READ) = 0
    munmap(0x7fe284837000, 95204)           = 0
    getpid()                                = 7424
    fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
    brk(NULL)                               = 0x5560f9a93000
    brk(0x5560f9ab4000)                     = 0x5560f9ab4000
    write(1, "Processo pai com PID: 7424\n\n", 28) = 28
    clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7fe284836790) = 7425
    clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7fe284836790) = 7426
    clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7fe284836790) = 7427
    --- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=7425, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
    wait4(7425, [{WIFEXITED(s) && WEXITSTATUS(s) == 0}], 0, NULL) = 7425
    write(1, "\n", 1)                       = 1
    --- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=7426, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
    write(1, "Finalizou o processo filho com P"..., 41) = 41
    write(1, "Restam 2 processos filhos ativos"..., 33) = 33
    wait4(7426, [{WIFEXITED(s) && WEXITSTATUS(s) == 0}], 0, NULL) = 7426
    write(1, "\n", 1)                       = 1
    write(1, "Finalizou o processo filho com P"..., 41) = 41
    write(1, "Restam 1 processos filhos ativos"..., 33) = 33
    wait4(7427, [{WIFEXITED(s) && WEXITSTATUS(s) == 0}], 0, NULL) = 7427
    --- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=7427, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
    write(1, "\n", 1)                       = 1
    write(1, "Finalizou o processo filho com P"..., 41) = 41
    write(1, "Restam 0 processos filhos ativos"..., 33) = 33
    exit_group(0)                           = ?
    +++ exited with 0 +++
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
    23.02    0.000154          31         5           mmap
    18.54    0.000124          31         4           mprotect
    10.16    0.000068          23         3         3 access
    9.57    0.000064          32         2           openat
    8.37    0.000056          56         1           munmap
    7.47    0.000050          17         3           brk
    7.32    0.000049          16         3           fstat
    4.48    0.000030          15         2           close
    3.14    0.000021          21         1           read
    3.14    0.000021          21         1           arch_prctl
    2.84    0.000019          19         1           execve
    1.94    0.000013          13         1           getpid
    0.00    0.000000           0        10           write
    0.00    0.000000           0         3           clone
    0.00    0.000000           0         3           wait4
    ------ ----------- ----------- --------- --------- ----------------
    100.00    0.000669                    43         3 total

Nesse log é possível notar que a chamada `wait4` é invocada três vezes, uma para cada chamada do `waitpid` em cada filho encerrado via código em C. Os processos filhos monitorados são 7425, 7426 e 7427.

#### 1.2.3	execve
A função `execve()` serve para acionar a execução de um programa descrito no argumento `filename`. A entrada desse argumento pode ser tanto um arquivo binário executável quanto um script. Quando obtém sucesso na abertura do arquivo, o `execve()` não possui retorno, enquanto em caso de erro retorna -1.

O código implementado para utilização do `execve()` nesse projeto pode ser acessado em https://github.com/rogerscristo/SSC5723-gpso3/blob/master/M%C3%B3dulo%201/Chamadas%20de%20Sistema/Gerenciamento%20de%20Processos/execve/execve.c. Para realizar a análise utilizando o `strace` o seguinte comando foi executado:

    strace -o strace_execve_dump -C ./execve.o

O retorno do strace para o código desenvolvido é apresentado abaixo:

    execve("./execve.o", ["./execve.o"], 0x7ffeb254df38 /* 78 vars */) = 0
    brk(NULL)                               = 0x558e6700f000
    access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
    access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
    fstat(3, {st_mode=S_IFREG|0644, st_size=95204, ...}) = 0
    mmap(NULL, 95204, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fa9aeea6000
    close(3)                                = 0
    access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
    read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260\34\2\0\0\0\0\0"..., 832) = 832
    fstat(3, {st_mode=S_IFREG|0755, st_size=2030544, ...}) = 0
    mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fa9aeea4000
    mmap(NULL, 4131552, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fa9ae8a6000
    mprotect(0x7fa9aea8d000, 2097152, PROT_NONE) = 0
    mmap(0x7fa9aec8d000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7fa9aec8d000
    mmap(0x7fa9aec93000, 15072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fa9aec93000
    close(3)                                = 0
    arch_prctl(ARCH_SET_FS, 0x7fa9aeea54c0) = 0
    mprotect(0x7fa9aec8d000, 16384, PROT_READ) = 0
    mprotect(0x558e6694d000, 4096, PROT_READ) = 0
    mprotect(0x7fa9aeebe000, 4096, PROT_READ) = 0
    munmap(0x7fa9aeea6000, 95204)           = 0
    execve("/bin/echo", ["/bin/echo", "Esse \303\251 um echo executado com ex"...], 0x7ffc41135f78 /* 0 vars */) = 0
    brk(NULL)                               = 0x556999b82000
    access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
    access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
    fstat(3, {st_mode=S_IFREG|0644, st_size=95204, ...}) = 0
    mmap(NULL, 95204, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fcc2791f000
    close(3)                                = 0
    access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
    read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260\34\2\0\0\0\0\0"..., 832) = 832
    fstat(3, {st_mode=S_IFREG|0755, st_size=2030544, ...}) = 0
    mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fcc2791d000
    mmap(NULL, 4131552, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fcc2731f000
    mprotect(0x7fcc27506000, 2097152, PROT_NONE) = 0
    mmap(0x7fcc27706000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7fcc27706000
    mmap(0x7fcc2770c000, 15072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fcc2770c000
    close(3)                                = 0
    arch_prctl(ARCH_SET_FS, 0x7fcc2791e540) = 0
    mprotect(0x7fcc27706000, 16384, PROT_READ) = 0
    mprotect(0x5569997d2000, 4096, PROT_READ) = 0
    mprotect(0x7fcc27937000, 4096, PROT_READ) = 0
    munmap(0x7fcc2791f000, 95204)           = 0
    brk(NULL)                               = 0x556999b82000
    brk(0x556999ba3000)                     = 0x556999ba3000
    fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
    write(1, "Esse \303\251 um echo executado com ex"..., 37) = 37
    close(1)                                = 0
    close(2)                                = 0
    exit_group(0)                           = ?
    +++ exited with 0 +++
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
    20.17    0.000119          15         8           mprotect
    20.00    0.000118          12        10           mmap
    13.56    0.000080          40         2           munmap
    13.05    0.000077          13         6         6 access
    8.64    0.000051          13         4           openat
    6.10    0.000036           6         6           close
    4.58    0.000027          14         2           execve
    4.07    0.000024           6         4           brk
    3.56    0.000021           4         5           fstat
    3.05    0.000018          18         1           write
    2.03    0.000012           6         2           read
    1.19    0.000007           4         2           arch_prctl
    ------ ----------- ----------- --------- --------- ----------------
    100.00    0.000590                    52         6 total

A execução do `strace` para o código proposto revela duas chamadas do `execve()`. A primeira referece a execução do binário gerado pela compilação do código `execve.c`. As chamadas de sistema na sequência realizam as alocações em disco e memória necessárias. A segunda chamada do `execve` referece a execução da função `echo` implementada no código em C.

### 1.3 Gerenciamento de arquivos
As três chamadas de sistema implementadas para demonstrar o gerenciamento de arquivos foram: `stat`, `lseek` e `open`. Para acessar o código de cada uma das três entre em https://github.com/rogerscristo/SSC5723-gpso3/tree/master/M%C3%B3dulo%201/Chamadas%20de%20Sistema/Gerenciamento%20de%20Arquivos.

#### 1.3.1	stat
A função `execve()` serve para acionar a execução de um programa descrito no argumento `filename`. A entrada desse argumento pode ser tanto um arquivo binário executável quanto um script. Quando obtém sucesso na abertura do arquivo, o `execve()` não possui retorno, enquanto em caso de erro retorna -1.

O código implementado para utilização do `stat()` nesse projeto pode ser acessado em https://github.com/rogerscristo/SSC5723-gpso3/blob/master/M%C3%B3dulo%201/Chamadas%20de%20Sistema/Gerenciamento%20de%20Arquivos/stat/stat.c. Neste código, a função `stat()` é invocada para retornar algumas estatísticas a repeito do próprio arquivo `stat.c` (Permissões do arquivo, id do despositivo no qual o arquivo `stat.c` reside, tamanho do arquivo e horário da última alteração no arquivo).

Para realizar a análise utilizando o `strace` o seguinte comando foi executado:

    strace -o strace_stat_dump -C ./stat.o

O retorno do strace para o código desenvolvido é apresentado abaixo:

    execve("./stat.o", ["./stat.o"], 0x7ffe79f9b1c8 /* 78 vars */) = 0
    brk(NULL)                               = 0x563076f14000
    access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
    access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
    fstat(3, {st_mode=S_IFREG|0644, st_size=95204, ...}) = 0
    mmap(NULL, 95204, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f67a4897000
    close(3)                                = 0
    access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
    openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
    read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260\34\2\0\0\0\0\0"..., 832) = 832
    fstat(3, {st_mode=S_IFREG|0755, st_size=2030544, ...}) = 0
    mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f67a4895000
    mmap(NULL, 4131552, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f67a4297000
    mprotect(0x7f67a447e000, 2097152, PROT_NONE) = 0
    mmap(0x7f67a467e000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7f67a467e000
    mmap(0x7f67a4684000, 15072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f67a4684000
    close(3)                                = 0
    arch_prctl(ARCH_SET_FS, 0x7f67a48964c0) = 0
    mprotect(0x7f67a467e000, 16384, PROT_READ) = 0
    mprotect(0x563075107000, 4096, PROT_READ) = 0
    mprotect(0x7f67a48af000, 4096, PROT_READ) = 0
    munmap(0x7f67a4897000, 95204)           = 0
    stat("stat.c", {st_mode=S_IFREG|0664, st_size=1003, ...}) = 0
    fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
    brk(NULL)                               = 0x563076f14000
    brk(0x563076f35000)                     = 0x563076f35000
    write(1, "Stats do arquivo stats.c\n", 25) = 25
    write(1, "Permiss\303\265es do arquivo: st_mode "..., 41) = 41
    write(1, "ID do dispositivo no qual o arqu"..., 65) = 65
    write(1, "Tamanho do arquivo (bytes): st_s"..., 43) = 43
    write(1, "Hor\303\241rio da \303\272ltima altera\303\247\303\243o "..., 66) = 66
    exit_group(0)                           = ?
    +++ exited with 0 +++
    % time     seconds  usecs/call     calls    errors syscall
    ------ ----------- ----------- --------- --------- ----------------
    17.65    0.000084          28         3           brk
    15.55    0.000074          15         5           write
    12.82    0.000061          15         4           mprotect
    12.61    0.000060          60         1           execve
    10.50    0.000050          10         5           mmap
    9.45    0.000045          45         1           munmap
    5.67    0.000027           9         3         3 access
    5.46    0.000026           9         3           fstat
    4.83    0.000023          12         2           openat
    2.31    0.000011          11         1           stat
    1.26    0.000006           3         2           close
    1.05    0.000005           5         1           read
    0.84    0.000004           4         1           arch_prctl
    ------ ----------- ----------- --------- --------- ----------------
    100.00    0.000476                    32         3 total


A única chamada `stat` do log se refere a execução de todos os 4 parâmetros solicitados: `st_mode`, `st_size`, `st_dev` e `st_mtime`. Todos estes modos são declarados numa `struct` presente em sua implementação:

``` c
struct stat {
    dev_t     st_dev;         /* ID of device containing file */
    ino_t     st_ino;         /* Inode number */
    mode_t    st_mode;        /* File type and mode */
    nlink_t   st_nlink;       /* Number of hard links */
    uid_t     st_uid;         /* User ID of owner */
    gid_t     st_gid;         /* Group ID of owner */
    dev_t     st_rdev;        /* Device ID (if special file) */
    off_t     st_size;        /* Total size, in bytes */
    blksize_t st_blksize;     /* Block size for filesystem I/O */
    blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

    /* Since Linux 2.6, the kernel supports nanosecond
        precision for the following timestamp fields.
        For the details before Linux 2.6, see NOTES. */

    struct timespec st_atim;  /* Time of last access */
    struct timespec st_mtim;  /* Time of last modification */
    struct timespec st_ctim;  /* Time of last status change */

    #define st_atime st_atim.tv_sec      /* Backward compatibility */
    #define st_mtime st_mtim.tv_sec
    #define st_ctime st_ctim.tv_sec
};
```

#### 1.3.2	lseek
TODO: Fazer descrição nos moldes das anteriores.

#### 1.3.3	open
TODO: Fazer descrição nos moldes das anteriores.

### 1.4 Gerenciamento de memória
TODO: Fazer descrição similar a da seção Gerenciamento de processos

#### 1.4.1	getrlimit
TODO: Fazer descrição nos moldes das anteriores.

#### 1.4.2	setrlimit
TODO: Fazer descrição nos moldes das anteriores.

#### 1.4.3	sbrk
TODO: Fazer descrição nos moldes das anteriores.

-------
## 2. Processos CPU-bound e I-O bound  

Cada grupo deverá desenvolver ao menos 2 programas que exibam o comportamento esperado para processos CPU-bound e I-O bound, tal como foi informado em sala de aula. Pode-se utilizar os programas desenvolvidos na etapa anterior, desde que eles atendam ao requisito especificado. 