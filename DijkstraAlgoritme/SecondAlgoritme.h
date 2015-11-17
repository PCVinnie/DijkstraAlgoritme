#ifndef SecondAlgoritme_H
#define SecondAlgoritme_H

#define V 5

class SecondAlgoritme {

public:
	//Constructor
	SecondAlgoritme();
	//SecondAlgoritme(int[V][V]);

	//Destructor
	~SecondAlgoritme();

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