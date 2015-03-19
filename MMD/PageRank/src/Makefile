objects=main.o algorithm.o

all : pagerank
CXXFLAGS= -g -O2 

pagerank : $(objects)
	g++ -o pagerank $(objects) -O2

main.o : algorithm.h
algorithm.o : algorithm.h

.PHONY : clean all

clean :
	rm -rf $(objects) pagerank
