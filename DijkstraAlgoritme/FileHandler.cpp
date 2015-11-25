#include "stdafx.h"
#include <iostream>
#include <fstream>

#include <string>
#include <sstream>
#include <vector>
#include "FileHandler.h"

FileHandler::FileHandler() { }

FileHandler::~FileHandler() { }

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

/*

int** FileHandler::openTxtFile(std::string filename) {

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
	file.open(filename);
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

*/

/*
*	Opdracht: 25.8 file IO voor een graph.
*/

int** FileHandler::openTxtFile(std::string filename) {

	std::string line;
	int column = 0;
	int size = 0;
	bool asSize = true;
	bool asLine = false;

	// Tweedimensionale array
	int** graph = new int*[12];
	for (int i = 0; i < 12; ++i) {
		graph[i] = new int[12];
	}

	// Maakt alles in de tweedimensionale array nul.
	for (int row = 0; row < 12; row++) {
		for (int column = 0; column < 12; column++) {
			graph[row][column] = 0;
		}
	}

	std::ifstream file;
	file.open(filename);
	if (file.is_open()) {
		while (getline(file, line)) {

			// Controleert de grootte van de graph.
			if (asSize == true) {
				size = atoi(line.c_str());
				asSize = false;
			}

			// Haalt de graph op en schrijft dit weg naar een tweedimensionale array.
			if (asLine == true) {

				int r = INT_MAX;
				int c = INT_MAX;
				int weight = INT_MAX;
				bool asWeight = false;
				bool asReset = false;

					// Splitst de string eerst op met het sluisteken, vervolgens wordt de uitkomst ook weer gesplitst met komma's.
					for (int row = 0; row < split(line, '|').size(); row++) {
						std::string tmp1 = split(line, '|').at(row).c_str();
						for (int i = 0; i < split(tmp1, ',').size(); i++) {
							std::string tmp = split(tmp1, ',').at(i).c_str();

							// Stap 3: Daarna wordt de weight op de juiste positie in de graph toegewezen.
							if (asWeight == true) {
								weight = stoi(tmp);
								// Zorgt dat de weight op de juiste positie in de graph wordt toegewezen.
								graph[r][c] = stoi(tmp);
								graph[c][r] = stoi(tmp);
								asWeight = false;
								asReset = true;
							}

							// Stap 1: Eerst wordt de row aan toegewezen r.
							if (r == INT_MAX) {
								r = stoi(tmp);
							}
							else {
								// Stap 2: Vervolgens wordt de column toegewezen c en wordt asWeight op true gezet.
								if (c == INT_MAX) {
									c = stoi(tmp);
									asWeight = true;
								}
							}

							// Stap 4: INT_MAX wordt voor de row, column en weight opnieuw toegewezen.
							if (asReset == true) {
								r = INT_MAX; c = INT_MAX; weight = INT_MAX;
								asReset = false;
							}
						}

					}

					// Stap 5: Verhoogt de column als de volledige row aan de graph is toegewezen.
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
