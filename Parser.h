#ifndef PARSER_H_
#define PARSER_H_

#include "Database.h"
#include "ConditionList.h"
#include "Condition.h"

#include <vector>


class Parser{

	Database& database;

	
	
		//IO FUNCTIONS
		//These are functions which deal with files and commands have already been parsed for the most part
	
	//TODO
	int writeFile(string relationName);
	
	//TODO 
	//Opens a file by relation name, and parses all commands in file.
	int openFile(string relationName);
	
	//TODO
	//Close a file when done
	int closeFile(string relationName);
	
	//PARSER/STRINGSTREAM FUNCTIONS
	
	
	
		//COMMANDS
		//The command itself ("insert into", "create table", "delete from", "update") has already been read by the parser
	
	
	
	//TODO
	//Parse the rest of a create table command
	int createTable(stringstream& command);
	
	//TODO
	//Parse the rest of delete from command
	int deleteFrom(stringstream& command);
	
	//TODO
	//Parse the rest of insert into command
	int insertInto(stringstream& command);
	
	//TODO
	//Parse the rest of update command
	int update(stringstream& command);
	
	
	
		//QUERIES
		//The query command ("project", "select", "rename", etc.) has already been read by the parser
		
	
	//TODO
	Relation selection(stringstream& command);
	
	//TODO
	Relation projection(stringstream& command);
	
	//TODO
	Relation relationUnion(stringstream& command);
	
	//TODO
	Relation difference(stringstream& command);
	
	//TODO
	Relation crossProduct(stringstream& command);
	
	//TODO
	Relation naturalJoin(stringstream& command);
	
	//TODO
	Relation rename(stringstream& command);
	
	
	
		//GENERAL PARSER FUNCTIONS
		

	//TODO
	//Peeks to see if next character is a plus sign;
	int peekAddition(stringstream& command);

	//TODO
	//Peeks to see if next character is a minus sign;
	int peekSubtraction(stringstream& command);

	//TODO
	//Peeks to see if next character is a * sign;
	int peekMultiplication(stringstream& command);

	//TODO
	//Reads in an arrow, "<-". Returns 1 for success, -1 for failure.
	int readArrow(stringstream& command);
	
	//TODO
	//reads a semicolon. Returns -1 if failed.
	int readSemi(stringstream& command);
	
	//TODO
	//Reads whitespace
	void readWhite(stringstream& command);

	//TODO
	//reads and returns an alphanumeric word from the stream. (a-z, A-Z, 0-9, _)
	//This function first reads through any whitespace and then stores the word
	string readAlphaNumWord(stringstream& command);
	
	//TODO
	//takes in a stream which has been identified as a condition and returns the resulting condition list
	vector<Condition> parseConditions(stringstream& command);
	
	//TODO
	//takes in a stream which has been identified as a query and returns a relation
	//Return NULL if error.
	//OFTEN CALLED RECURSIVELY
	Relation parseExpr(stringstream& command);

	//TODO
	//Reads in a query - ie. "relationName" <- expr
	int parseQuery(stringstream& command);

	//UNDER CONSTRUCTION
	//takes in a stream which may be a command and updates information - returns -1 for error
	int parseCommand(stringstream& command);
	
public:

	Parser(Database& d) : database(d) {}

	int parse(string command);
	
	
};

#endif