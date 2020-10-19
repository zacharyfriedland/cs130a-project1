# Makefile
all: main.o tst.o
	g++ -std=c++11 main.o tst.o -o project1.out

tst: tst.o
	g++ -std=c++11 tst.cpp -c tst.o

clean:
	/bin/rm -f project1.out *.o