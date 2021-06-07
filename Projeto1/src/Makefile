CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g

all: progrest progrdin
	rm *.o
progrdin: main.o elemento.o flags.o listaDIN.o paths.o qry.o svg.o system.o
	$(CC) $(CFLAGS) main.o elemento.o flags.o listaDIN.o paths.o qry.o svg.o system.o -o progrdin
progrest: main.o elemento.o flags.o listaEST.o paths.o qry.o svg.o system.o
	$(CC) $(CFLAGS) main.o elemento.o flags.o listaEST.o paths.o qry.o svg.o system.o -o progrest
main.o: main.c bibliotecas.h lista.h system.h flags.h paths.h svg.h
	$(CC) $(CFLAGS) -c main.c 
elemento.o: elemento.c elemento.h
	$(CC) $(CFLAGS) -c elemento.c
flags.o: flags.c flags.h
	$(CC) $(CFLAGS) -c flags.c
listaDIN.o: listaDIN.c bibliotecas.h lista.h
	$(CC) $(CFLAGS) -c listaDIN.c
listaEST.o: listaEST.c bibliotecas.h lista.h
	$(CC) $(CFLAGS) -c listaEST.c
paths.o: paths.c paths.h
	$(CC) $(CFLAGS) -c paths.c
qry.o: qry.c qry.h elemento.o flags.o
	$(CC) $(CFLAGS) -c qry.c
svg.o: svg.c svg.h flags.h paths.h
	$(CC) $(CFLAGS) -c svg.c
system.o: system.c system.h bibliotecas.h qry.h elemento.h flags.h paths.h svg.h
	$(CC) $(CFLAGS) -c system.c