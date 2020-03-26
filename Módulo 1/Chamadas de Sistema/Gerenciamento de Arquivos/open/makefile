all: 
	@gcc open.c -o open.o
	@strace -o strace_open_dump -C ./open.o

clean:
	@rm *.o