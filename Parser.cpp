#include "Parser.h"
#include <sstream>

#define SUCCESS 1
#define INVALID 0
#define EXIT -1

//TODO
string readAlphaNumWord(stringstream& command);


//UNDER CONSTRUCTION
int Parse::parseCommand(stringstream& command){

	string word = readAlphaNumWord(command);
	
	if( word == "OPEN" ){
	
		string relationName = readAlphaNumWord(command);
		
		//Catch problem before execution
		if( readSemi(command) < 0){
			return INVALID;
		}
		
		openFile(relationName);
		
		return SUCCESS;
	
	}else if( word == "SHOW ){
	
		string relationName = readAlphaNumWord(command);
		
		//Catch problem before execution
		if( readSemi(command) < 0){
			return INVALID;
		}
	
		cout<< *database.accessRelation(relationName);
	
		return SUCCESS;
	
	}else if( word == "

}

Relation* Parser::parseExpr(stringstream& command){

	//Find command it matches to.
	
	//If none is it a new assignment?

}

int Parser::parse(string s){

	if(s == "EXIT"){
		return EXIT;
	}

	stringstream command;
	command>>s;
	
	//Try to parse it as a command - if it returns error, then we continue
	if(parseCommand(command) > 0){
		
		return SUCCESS;
	
	}

	//Restore the command
	command.clear();
	command>>s;

	Relation* r = parseQuery(command);

	if( r == NULL ){
	
		return INVALID;
	
	}

	database.addRelationToDatabase(
	
}



























