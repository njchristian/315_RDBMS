#include "Parser.h"
#include <iostream>
#include <sstream>

#define SUCCESS 1
#define INVALID -1
#define EXIT -2

//TODO
string readAlphaNumWord(stringstream& command);


//UNDER CONSTRUCTION
int Parser::parseCommand(stringstream& command){

	string word = readAlphaNumWord(command);
	
	if( word == "OPEN" ){
	
		string relationName = readAlphaNumWord(command);
		
		//Catch problem before execution
		if( readSemi(command) < 0){
			return INVALID;
		}
		
		openFile(relationName);
		
		return SUCCESS;
	
	}else if( word == "CLOSE" ){
	
		string relationName = readAlphaNumWord(command);

		if( closeFile(relationName) < 0 ){
			return INVALID;
		}

		if( readSemi(command) < 0){
			return INVALID;
		}

	}else if( word == "SHOW" ){
	
		string relationName = readAlphaNumWord(command);
		
		//Catch problem before execution
		if( readSemi(command) < 0){
			return INVALID;
		}
	
		cout<< *database.accessRelation(relationName);
	
		return SUCCESS;
	
	}else if( word == "WRITE" ){

		string relationName = readAlphaNumWord(command);
		
		//Catch problem before execution
		if( readSemi(command) < 0){
			return INVALID;
		}

		if( writeFile(relationName) < 0){
			return INVALID;
		}

		return SUCCESS;

	}else if( word == "INSERT" ){

		string into = readAlphaNumWord(command);

		if( into != "INTO" ){
			return INVALID;
		}

		if( insertInto(command) < 0){
			return INVALID;
		}

		return SUCCESS;

	}else if( word == "DELETE" ){

		string from = readAlphaNumWord(command);

		if( from != "FROM" ){
			return INVALID;
		}

		if( deleteFrom(command) < 0){
			return INVALID;
		}

		return SUCCESS;

	}else if( word == "CREATE" ){
		string table = readAlphaNumWord(command);

		if( table != "TABLE" ){
			return INVALID;
		}

		if( createTable(command) < 0){
			return INVALID;
		}

		return SUCCESS;

	}else if( word == "UPDATE" ){

		if( update(command) < 0){
			return INVALID;
		}

		return SUCCESS;

	}else{

		return INVALID;

	}

}

//TODO
Relation Parser::projection(stringstream& command){


}

//DONE - NOT DEBUGGED
int Parser::parseQuery(stringstream& command){

	string relationName = readAlphaNumWord(command);

	if( readArrow(command) < 0){
		return INVALID;
	}

	Relation targetRelation = parseExpr(command);

	if( targetRelation.isEmpty() ){
		return INVALID;
	}

	database.addRelationToDatabase(targetRelation);

	return SUCCESS;

}

//DONE - NOT DEBUGGED
Relation Parser::parseExpr(stringstream& command){

	//Find command it matches to.

	//Could be word, or relation name, or relation name followed by +/-

	string word = readAlphaNumWord(command);

	Relation targetRelation;

	if( word == "project" ){

		targetRelation = projection(command);

		return targetRelation;

	}else if( word == "select" ){

		targetRelation = selection(command);

		return targetRelation;

	}else if( word == "rename" ){

		targetRelation = rename(command);

		return targetRelation;

	}else{

		//At this point we assume what we have is the name of a relation

		string relationA = word;


		if( readSemi(command) > 0 ){

			targetRelation = *database.accessRelation(relationA);

			return targetRelation;

		}else if( peekAddition(command) > 0 ){

			string relationB = readAlphaNumWord(command);


			targetRelation = database.unionTwoRelations(relationA, relationB);

			return targetRelation;
			
		}else if( peekSubtraction(command) > 0){

			string relationB = readAlphaNumWord(command);


			targetRelation = database.differenceTwoRelation(relationA, relationB);

			return targetRelation;

		}else if( peekMultiplication(command) > 0){

			string relationB = readAlphaNumWord(command);


			targetRelation = database.crossProduct(relationA, relationB);

			return targetRelation;

		}else{

			string join = readAlphaNumWord(command);

			if( join != "JOIN" ){
				return Relation();
			}

			string relationB = readAlphaNumWord(command);
		

			targetRelation = database.naturalJoin(relationA, relationB);

			return targetRelation;

		}


	}


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

	if( parseQuery(command) > 0 ){
		return SUCCESS;
	}

	return INVALID;
}



























