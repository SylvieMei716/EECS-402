all: proj4.exe

proj4.exe: LinkedNodeClass.o SortedListClass.o LIFOStackClass.o FIFOQueueClass.o project4.o
	g++ -Wall -g -std=c++98 LinkedNodeClass.o SortedListClass.o LIFOStackClass.o FIFOQueueClass.o project4.o -o proj4.exe

project4.o: project4.cpp LinkedNodeClass.o SortedListClass.o LIFOStackClass.o FIFOQueueClass.o
	g++ -g -std=c++98 -Wall -c project4.cpp -o project4.o

LinkedNodeClass.o: LinkedNodeClass.cpp LinkedNodeClass.h
	g++ -g -std=c++98 -Wall -c LinkedNodeClass.cpp -o LinkedNodeClass.o

SortedListClass.o: SortedListClass.cpp SortedListClass.h
	g++ -g -std=c++98 -Wall -c SortedListClass.cpp -o SortedListClass.o

LIFOStackClass.o: LIFOStackClass.cpp LIFOStackClass.h
	g++ -g -std=c++98 -Wall -c LIFOStackClass.cpp -o LIFOStackClass.o

FIFOQueueClass.o: FIFOQueueClass.cpp FIFOQueueClass.h
	g++ -g -std=c++98 -Wall -c FIFOQueueClass.cpp -o FIFOQueueClass.o

clean:
	rm -f LinkedNodeClass.o SortedListClass.o LIFOStackClass.o FIFOQueueClass.o project4.o proj4.exe