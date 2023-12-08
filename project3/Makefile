all: proj3.exe

proj3.exe: ColorClass.o RowColumnClass.o ColorImageClass.o printColorChoices.o project3.o
	g++ -Wall -g -std=c++98 ColorClass.o RowColumnClass.o ColorImageClass.o printColorChoices.o project3.o -o proj3.exe

project3.o: project3.cpp ColorClass.o RowColumnClass.o ColorImageClass.o printColorChoices.o constants.h
	g++ -g -std=c++98 -Wall -c project3.cpp -o project3.o

ColorClass.o: ColorClass.cpp ColorClass.h
	g++ -g -std=c++98 -Wall -c ColorClass.cpp -o ColorClass.o

RowColumnClass.o: RowColumnClass.cpp RowColumnClass.h
	g++ -g -std=c++98 -Wall -c RowColumnClass.cpp -o RowColumnClass.o

ColorImageClass.o: ColorImageClass.cpp ColorImageClass.h
	g++ -g -std=c++98 -Wall -c ColorImageClass.cpp -o ColorImageClass.o

printColorChoices.o: printColorChoices.cpp printColorChoices.h
	g++ -g -std=c++98 -Wall -c printColorChoices.cpp -o printColorChoices.o

clean:
	rm -f ColorClass.o RowColumnClass.o ColorImageClass.o printColorChoices.o project3.o proj3.exe