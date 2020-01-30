driver.out: InnerSquareList.o SquareList.o Proj1Test.o
	g++ -Wall InnerSquareList.o SquareList.o Proj1Test.o -o driver.out

InnerSquareList.o: InnerSquareList.cpp InnerSquareList.h
	g++ -Wall -c InnerSquareList.cpp

SquareList.o: SquareList.cpp SquareList.h
	g++ -Wall -c SquareList.cpp

Proj1Test.o: Proj1Test.cpp SquareList.h
	g++ -Wall -c Proj1Test.cpp

clean:
	rm -rf *.o
	rm -f *.out

run:
	./driver.out
