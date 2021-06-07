CC = gcc
CFLAGS = -std=c99 -fstack-protector-all -g

progr: main.o paths.o system.o rectangle.o circle.o kdTree.o svg.o qry.o segments.o dynamicList.o polygon.o normalTree.o
	$(CC) $(CFLAGS) main.o paths.o system.o rectangle.o circle.o kdTree.o svg.o qry.o segments.o dynamicList.o polygon.o normalTree.o -o progr -lm 
main.o: main.c bibliotecas.h system.h kdTree.h paths.h  circle.h rectangle.h
	$(CC) $(CFLAGS) -c main.c
paths.o: paths.c paths.h
	$(CC) $(CFLAGS) -c paths.c
system.o: system.c bibliotecas.h system.h  paths.h rectangle.h circle.h kdTree.h qry.h svg.h
	$(CC) $(CFLAGS) -c system.c 
rectangle.o: rectangle.c rectangle.h 
	$(CC) $(CFLAGS) -c rectangle.c
circle.o: circle.c circle.h 
	$(CC) $(CFLAGS) -c circle.c
kdTree.o: kdTree.c kdTree.h rectangle.h circle.h
	$(CC) $(CFLAGS) -c kdTree.c
svg.o: svg.c svg.h
	$(CC) $(CFLAGS) -c svg.c
qry.o: qry.c qry.h
	$(CC) $(CFLAGS) -c qry.c
segments.o: segments.c segments.h
	$(CC) $(CFLAGS) -c segments.c
dynamicList.o: dynamicList.c dynamicList.h
	$(CC) $(CFLAGS) -c dynamicList.c
polygon.o: polygon.c polygon.h
	$(CC) $(CFLAGS) -c polygon.c
normalTree.o: normalTree.c normalTree.h
	$(CC) $(CFLAGS) -c normalTree.c