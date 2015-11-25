#ifndef FileHandler_H
#define FileHandler_H

class FileHandler {

public:
	//Constructor
	FileHandler();

	//Destructor
	~FileHandler();

	//Methods
	int** openTxtFile(std::string);
	int** openTxtFileFormat(std::string);

};

#endif