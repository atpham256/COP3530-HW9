all:
	${MAKE}  hw9
hw9: hw9.o
	g++ -g -Wall -o hw9 hw9.o
hw9.o: hw9.cpp
	g++ -g -Wall -c hw9.cpp
clean:
	rm *.o hw9