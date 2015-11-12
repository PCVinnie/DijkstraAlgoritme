#include "stdafx.h"
#include <iostream>
#include "limits.h"
#include "SecondAlgoritme.h"

using namespace std;

SecondAlgoritme::SecondAlgoritme() { };

SecondAlgoritme::SecondAlgoritme(int vertices[V][V]) { 

	this->vertices[V][V] = vertices[V][V];

};

SecondAlgoritme::~SecondAlgoritme() { };

/*
	Haalt de loopings weg door het te vervangen met een 0.
*/
void SecondAlgoritme::removeLoopings() {

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
void SecondAlgoritme::removeParallel() {
	
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
int SecondAlgoritme::distance(int dist[V][V]) {

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
void SecondAlgoritme::printTerminal(int dist[V][V]) {

	cout << "Het kortste pad is: \n" << endl;
	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			printf(">" + dist[row][column]);
		}
	}

}

void SecondAlgoritme::dijkstra() {

	removeLoopings();
	printTerminal(vertices);

	removeParallel();
	printTerminal(vertices);

	int dist[V][V];

	// Vult de matrix met -1
	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			dist[row][column] = -1;
		}
	}
	
	// Geeft de eerste positie van de matrix een 0
	dist[0][0] = 0;
	
	// Berekent de kortste afstand
	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			//dist[V][V] = distance(vertices);
			if (dist[row][column] != -1) {
				dist[row][column] = dist[row][column] + vertices[row][column];
			}
		}
	}

	printTerminal(dist);

}