#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "Manager.h"

void printGreeting(ofstream& out)
{
	out << "Jasmine Leu, Section 502" << endl;
}

int main(int argc, char* argv[]) {
	std::ofstream outputFileStream;

	//take in store and order files
	Manager manager(argv[1], argv[2]);
	//open output file
	outputFileStream.open("results.txt");
	//print greeting
	printGreeting(outputFileStream);
	// Print Manager status
	manager.printStatus(outputFileStream);
	// Fill orders on Manager
	manager.fillOrders(outputFileStream);
	// Print Manager status
	manager.printStatus(outputFileStream);

	outputFileStream.close();

	return EXIT_SUCCESS;
}
