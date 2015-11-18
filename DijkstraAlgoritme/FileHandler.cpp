#include "stdafx.h"
#include <iostream>
#include <fstream>

#include <string>
#include <sstream>
#include <vector>
#include "FileHandler.h"

FileHandler::FileHandler() {

}

FileHandler::~FileHandler() {

}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

int** FileHandler::openTxtFile() {

	std::string line;
	int column = 0;
	int size = 0;
	bool asSize = true;
	bool asLine = false;

	int** graph = new int*[9];
	for (int i = 0; i < 9; ++i) {
		graph[i] = new int[9];
	}

	std::ifstream file;
	file.open("graph.txt");
	if (file.is_open()) {
		while (getline(file, line)) {

			// Controleert de grootte van de graph.
			if (asSize == true) {
				size = atoi(line.c_str());
				asSize = false;
			}

			// Haalt de graph op en schrijft dit weg naar een tweedimensionale array.
			if (asLine == true) {
				for (int row = 0; row < split(line, ' ').size(); row++) {
					graph[column][row] = atoi(split(line, ' ').at(row).c_str());
				}

				if (column < size) {
					column++;
				}
				else {
					column = 0;
				}
			}
			asLine = true;

		}

		std::cout << "Bestand is ingeladen." << std::endl;
		file.close();

	}
	else {
		std::cout << "Er is een fout opgetreden bij het openen of lezen van het bestand.";
	}

	return graph;

}
