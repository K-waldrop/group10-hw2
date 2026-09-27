CC = g++
CFLAGS = -std=c++11

all: main.o
	$(CC) $(CFLAGS) main.o -o a.out

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f *.o *.out