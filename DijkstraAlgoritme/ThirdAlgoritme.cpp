#include "stdafx.h"
#include <iostream>
#include "limits.h"
#include "ThirdAlgoritme.h"

ThirdAlgoritme::ThirdAlgoritme() { };

/*
SecondAlgoritme::SecondAlgoritme(int vertices[V][V]) { 

	this->vertices[V][V] = vertices[V][V];

};
*/

ThirdAlgoritme::~ThirdAlgoritme() { };

/*
	Haalt de loopings weg door het te vervangen met een 0.
*/
void ThirdAlgoritme::removeLoopings() {

	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			if (vertices[row][column] > 0 && row == column) {
				vertices[row][column] = 0;
			}
		}
	}
}

/*
	Haalt de parallelle verbindingen weg door het te vervangen met de hoogste waarden.
*/
void ThirdAlgoritme::removeParallel() {
	
	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			if (vertices[row][column] > 0) {			
				if (vertices[row][column] > vertices[column][row]) {
					vertices[column][row] = vertices[row][column];
				} else {
					vertices[row][column] = vertices[column][row];
				}
			}
		}
	}
}

/*
	Berekent de kortste afstand.
*/
int ThirdAlgoritme::distance(int dist[V][V]) {

	int total = 0;

	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			total = dist[0][0] + dist[0][0];
		}
	}

	return total;

}

/*
	Print de uitkomst in terminal.
*/
void ThirdAlgoritme::printTerminal(int dist[V][V]) {

	std::cout << "Output:" << std::endl;
	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			std::cout << dist[row][column] << ",";
		}
		std::cout << "" << std::endl;
	}
	std::cout << "" << std::endl;

}

void ThirdAlgoritme::dijkstra(int vertices[V][V]) {

	//removeLoopings();
	//printTerminal(vertices);

	//removeParallel();
	//printTerminal(vertices);

	int dist[V][V];

	// Vult de matrix met 0
	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			dist[row][column] = 0;
		}
	}
	
	// Berekent de kortste afstand
	for (int row = 1; row < V; row++) {
		for (int column = 1; column < V; column++) {

			if (vertices[row-1][column-1] == vertices[column-1][row-1]) {

				for (int row2 = 1; row2 < V; row2++) {

					dist[row2][column] = dist[row][column - 1] + vertices[row][column];

				}
			}
		}
	}

	printTerminal(dist);

}