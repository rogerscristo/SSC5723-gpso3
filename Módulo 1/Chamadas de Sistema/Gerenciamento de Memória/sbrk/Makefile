all:
	@gcc sbrk.c -o sbrk.o
	@strace -o strace_sbrk_dump -C ./sbrk.o

clean:
	@rm *.o