driver.out: Driver.o Manager.o Orders.o Order.o Store.o Food.o
	g++ -Wall -std=c++11 Driver.o Manager.o Orders.o Order.o Store.o Food.o -o driver.out

Driver.o: driver.cpp Manager.h
	g++ -Wall -std=c++11 -Wall -c Driver.cpp

Manager.o: Manager.cpp Manager.h Orders.h Store.h
	g++ -Wall -std=c++11 -c Manager.cpp

Orders.o: Orders.cpp Orders.h Order.h
	g++ -Wall -std=c++11 -c Orders.cpp

Order.o: Order.cpp Order.h Food.h
	g++ -Wall -std=c++11 -c Order.cpp

Store.o: Store.cpp Store.h Food.h
	g++ -Wall -std=c++11 -c Store.cpp

Food.o: Food.cpp Food.h
	g++ -Wall -std=c++11 -c Food.cpp

clean:
	rm -rf *.o
	rm -f *.out
	
run:
	./driver.out $(STORE) $(ORDERS)
