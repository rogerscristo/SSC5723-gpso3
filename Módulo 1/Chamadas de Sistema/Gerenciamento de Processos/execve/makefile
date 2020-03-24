all:
	@gcc execve.c -o execve.o

strace:
	@strace -o strace_execve_dump -C ./execve.o

clean:
	@rm *.o