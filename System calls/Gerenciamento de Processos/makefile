all:
	@gcc fork.c -o fork.o
	@strace -o strace_fork_dump -C ./fork.o

clean:
	@rm *.o