#ifndef FileHandler_H
#define FileHandler_H

class FileHandler {

public:
	//Constructor
	FileHandler();

	//Destructor
	~FileHandler();

	//Methods
	void writeTxtFile(int**, int);
	int** openTxtFile();

};

#endif