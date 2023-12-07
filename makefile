all: naktm client

naktm: naktm.o keymap.o keyboard-finder.o
	gcc -o naktm naktm.o keymap.o keyboard-finder.o

naktm.o: naktm.c
	gcc -c naktm.c

client: client.o
	gcc -o client client.c

client.o: client.c
	gcc -c client.c

keymap.o: keymap.c
	gcc -c keymap.c

keyboard-finder.o: keyboard-finder.c
	gcc -c keyboard-finder.c

clean:
	rm -f naktm naktm.o keymap.o keyboard-finder.o
