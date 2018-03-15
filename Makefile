CC=g++
CFLAGS=-I.
DEPS = Job.hpp
OBJ = main.o Job.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

simulate: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)
