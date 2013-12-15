objects = partone.o process.o
partone_objs = partone.o process.o
parttwo_objs = parttwo.o process.o

all : $(partone_objs) $(parttwo_objs)
	g++ -o project5_A $(partone_objs)
	g++ -o project5_B $(parttwo_objs)	
	make clean

process.o : process.cpp process.h global.h
	g++ -c -g -Wall process.cpp

partone.o : partone.cpp partone.h global.h process.h
	g++ -c -g -Wall -Wsign-compare partone.cpp

parttwo.o : parttwo.cpp parttwo.h global.h process.h memory.h
	g++ -c -g -Wall parttwo.cpp

clean :
	rm -f $(objects) $(partone_objs) $(parttwo_objs) log*.txt core
