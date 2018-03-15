CC=g++
CFLAGS=-I.

simulate: main.o Job.o
	$(CC) -o simulate  main.o Job.o -I.
