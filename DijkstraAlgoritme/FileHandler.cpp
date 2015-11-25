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

int** FileHandler::openTxtFile(std::string filename) {

	std::string line;
	int column = 0;
	int size = 0;
	bool asSize = true;
	bool asLine = false;

	int** graph = new int*[12];
	for (int i = 0; i < 12; ++i) {
		graph[i] = new int[12];
	}

	// Maakt alles 0.
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

			// 
			if (asLine == true) {

				int r = INT_MAX;
				int c = INT_MAX;
				int weight = INT_MAX;
				bool asWeight = false;
				bool asReset = false;

					for (int row = 0; row < split(line, '|').size(); row++) {
						std::string tmp1 = split(line, '|').at(row).c_str();
						for (int i = 0; i < split(tmp1, ',').size(); i++) {
							std::string tmp = split(tmp1, ',').at(i).c_str();

							if (asWeight == true) {
								weight = stoi(tmp);
								graph[r][c] = stoi(tmp);;
								asWeight = false;
								asReset = true;
							}

							if (r == INT_MAX) {
								r = stoi(tmp);
							}
							else {
								if (c == INT_MAX) {
									c = stoi(tmp);
									asWeight = true;
								}
							}

							if (asReset == true) {
								r = INT_MAX; c = INT_MAX; weight = INT_MAX;
								asReset = false;
							}
						}

					}

					if (column < size) {
						column++;
						r = INT_MAX; c = INT_MAX; weight = INT_MAX;
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
