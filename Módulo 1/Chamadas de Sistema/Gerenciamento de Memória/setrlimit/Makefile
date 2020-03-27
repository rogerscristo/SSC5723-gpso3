all:
	@gcc setrlimit.c -o setrlimit.o
	@strace -o strace_setrlimit_dump -C ./setrlimit.o

clean:
	@rm *.o