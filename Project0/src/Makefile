output.out: driver.o
	g++ -Wall driver.o -o output.out

Continent.o: Continent.cpp
	g++ -Wall -c Continent.cpp

Country.o: Country.cpp
	g++ -Wall -c Country.cpp

driver.o: driver.cpp Continent.o
	g++ -Wall -c driver.cpp

clean:
	rm -rf *.o
	rm -f *.out

run:
	./output.out
