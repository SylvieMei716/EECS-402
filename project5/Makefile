all: proj5.exe

proj5.exe: CarClass.o random.o EventClass.o IntersectionSimulationClass.o project5.o
	g++ -Wall -g -std=c++98 CarClass.o random.o EventClass.o IntersectionSimulationClass.o project5.o -o proj5.exe

project5.o: project5.cpp LinkedNodeClass.h SortedListClass.h FIFOQueueClass.h LinkedNodeClass.inl SortedListClass.inl FIFOQueueClass.inl CarClass.o random.o EventClass.o IntersectionSimulationClass.o constants.h
	g++ -g -std=c++98 -Wall -c project5.cpp -o project5.o

CarClass.o: CarClass.cpp CarClass.h
	g++ -g -std=c++98 -Wall -c CarClass.cpp -o CarClass.o

random.o: random.cpp random.h
	g++ -g -std=c++98 -Wall -c random.cpp -o random.o

EventClass.o: EventClass.cpp EventClass.h
	g++ -g -std=c++98 -Wall -c EventClass.cpp -o EventClass.o

IntersectionSimulationClass.o: IntersectionSimulationClass.cpp IntersectionSimulationClass.h
	g++ -g -std=c++98 -Wall -c IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

clean:
	rm -f CarClass.o random.o EventClass.o IntersectionSimulationClass.o project5.o proj5.exe