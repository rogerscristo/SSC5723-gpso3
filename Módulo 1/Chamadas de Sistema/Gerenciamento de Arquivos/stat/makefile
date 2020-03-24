
all: 
	@gcc stat.c -o stat.o

strace:
	@strace -o strace_stat_dump -C ./stat.o

clean:
	@rm *.o