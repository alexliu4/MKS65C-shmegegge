
all: share.o
	gcc share.o

share.o: share.c
	gcc -c share.c

clean:
	rm *.o
	rm a.out

run: all
	./a.out
	make clean
