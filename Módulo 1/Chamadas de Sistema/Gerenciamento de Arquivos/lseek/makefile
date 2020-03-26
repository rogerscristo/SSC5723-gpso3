all: 
	@gcc lseek.c -o lseek.o

strace:
	@strace -o strace_lseek_dump -C ./lseek.o

clean:
	@rm *.o