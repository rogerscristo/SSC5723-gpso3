all:
	@gcc getrlimit.c -o getrlimit.o
	@strace -o strace_getrlimit_dump -C ./getrlimit.o

clean:
	@rm *.o