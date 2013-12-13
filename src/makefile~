objects = partone.o process.o

all: $(objects)
	g++ -o project5B $(objects)
	make clean

process.o : process.cpp process.h
	g++ -c -g -Wall process.cpp

partone.o : partone.cpp partone.h global.h
	g++ -c -g -Wall -Wsign-compare partone.cpp

clean :
	rm -f $(objects) log*.txt core
