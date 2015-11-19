#ifndef ThirdAlgoritme_H
#define ThirdAlgoritme_H

#define V 5

class ThirdAlgoritme {

public:
	//Constructor
	ThirdAlgoritme();
	//SecondAlgoritme(int[V][V]);

	//Destructor
	~ThirdAlgoritme();

	//Methods
	void removeLoopings();
	void removeParallel();
	int distance(int[V][V]);
	void printTerminal(int[V][V]);
	void dijkstra(int [V][V]);

private:
	//Fields
	int vertices[V][V];

};

#endif