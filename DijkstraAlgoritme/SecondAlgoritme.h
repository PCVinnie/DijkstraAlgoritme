#ifndef SecondAlgoritme_H
#define SecondAlgoritme_H

#define V 9

class SecondAlgoritme {

public:
	//Constructor
	SecondAlgoritme();
	SecondAlgoritme(int[V][V]);

	//Destructor
	~SecondAlgoritme();

	//Methods
	void removeLoopings();
	void removeParallel();
	int distance(int[V][V]);
	void printTerminal(int[V][V]);
	void dijkstra();

private:
	//Fields
	int vertices[V][V];

};

#endif