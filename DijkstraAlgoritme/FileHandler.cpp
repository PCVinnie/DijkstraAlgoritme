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

void FileHandler::writeTxtFile(int** graph, int size) {
	std::ofstream file;
	file.open("graph.txt", std::ofstream::app); // std::ofstream::app voorkomt dat de inhoud wordt overschreven.
	if (file.is_open()) {
		for (int row = 0; row < size; row++) {
			for (int column = 0; column < size; column++) {
				file << graph[column][row] << " ";
			}
			file << std::endl;
		}
		file << " " << std::endl;
		file.close();
	}
	else {
		file.close();
		std::cout << "Er is een fout opgetreden bij het openen of lezen van het bestand.";
	}
}

int** FileHandler::openTxtFile() {

	std::string line;
	int column = 0;
	int tmp = 0;
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
			tmp = atoi(line.c_str());

			if (asLine == true) {
				for (int row = 0; row < split(line, ' ').size(); row++) {
					graph[column][row] = atoi(split(line, ' ').at(row).c_str());
				}

				if (column < 9) {
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
