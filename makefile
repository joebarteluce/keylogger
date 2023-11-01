naktm: naktm.o
	gcc -o naktm naktm.o

naktm.o: naktm.c
	gcc -c naktm.c

clean:
	rm -f naktm naktm.o
