#include "Parser.h"
#include "Database.h"

//FOR PART 2 WE DONT DEAL WITH THE DATABASE CELL
//THE DATABASE CELL IS THE GLUE BETWEEN THE PARSER AND THE DATABASE OBJECT
//IT IS ALSO WHAT THE USER SEES

class DBCell{

	Parser parser;
	Database database;

public:

	//...for example. This can be edited later
	void execute(string dmlCommand);

};