all:
	@gcc waitpid.c -o waitpid.o
	@strace -o strace_waitpid_dump -C ./waitpid.o

clean:
	@rm *.o