CC=g++
CFLAGS=-I.
DEPS = Job.hpp

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

simulate: main.o Job.o
	g++ -o simulate main.o Job.o -I.
