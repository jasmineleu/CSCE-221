driver.out: Driver.o Calculate.o
	g++ -Wall -std=c++11 Driver.o Calculate.o -o driver.out

Driver.o: Driver.cpp Calculate.h
	g++ -Wall -std=c++11 -c Driver.cpp

Calculate.o: Calculate.cpp Calculate.h
	g++ -Wall -std=c++11 -Wall -c Calculate.cpp


clean:
	rm -rf *.o
	rm -f *.out

run:
	./driver.out $(FILE)
