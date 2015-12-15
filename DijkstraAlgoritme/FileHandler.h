#ifndef FileHandler_H
#define FileHandler_H

class FileHandler {

public:
	//Constructor
	FileHandler();

	//Destructor
	~FileHandler();

	//Fields
	int size = 0;

	//Methods
	int** openTxtFile(std::string);
	int getSize();

};

#endif