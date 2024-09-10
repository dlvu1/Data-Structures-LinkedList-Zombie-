CC = g++
CFLAGS = -Wall -c $(DEBUG)
LFLAG = -Wall $(DEBUG)
DEBUG = -g
OBJS = hw5_Vu_Duyen.o zombie_Vu.o 

exe: hw5_Vu_Duyen.o zombie_Vu.o
	g++ -g hw5_Vu_Duyen.o zombie_Vu.o -o exe

hw5_Vu_Duyen.o: hw5_Vu_Duyen.cpp linkedlist_Vu.hpp zombie_Vu.h
	g++ -c -g hw5_Vu_Duyen.cpp

zombie_Vu.o: zombie_Vu.cpp zombie_Vu.h
	g++ -c -g zombie_Vu.cpp

clean:
	rm -f *.o exe