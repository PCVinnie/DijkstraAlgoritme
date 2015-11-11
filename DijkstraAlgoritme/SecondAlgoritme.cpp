#include "stdafx.h"
#include "limits.h"

#define V 5

int vertices[V][V];

/*
	Haalt de loopings weg door het te vervangen met een 0.
*/
void removeLoopings() {

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
void removeParallel() {
	
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
int distance(int dist[V][V]) {

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
void printTerminal(int dist[V][V]) {

	printf("Het kortste pad is: \n");
	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			printf("" + dist[row][column]);
		}
	}

}

void dijkstra(int vertices[V][V]) {

	removeLoopings();
	removeParallel();

	int dist[V][V];

	// Vult de matrix met 0en
	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			dist[row][column] = 0;
		}
	}
	
	// Berekent de kortste afstand
	for (int row = 0; row < V; row++) {
		for (int column = 0; column < V; column++) {
			//dist[V][V] = distance(vertices);

			//dist[row+1][column] = dist[row][column] + vertices[row][column];
		}
	}

	printTerminal(dist);

}

int main() {

	/*
		a -> a (Looping)
		d -> a (Parallel)
	*/
	int matrix[V][V] = { { 1, 1, 0, 1, 0 },
						 { 0, 0, 0, 1, 0 },
						 { 1, 0, 0, 0, 0 },
						 { 1, 0, 0, 0, 1 },
						 { 0, 0, 0, 0, 0 },
					   };

	dijkstra(matrix);

	getchar();
}