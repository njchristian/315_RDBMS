#ifndef PARSER_H_
#define PARSER_H_

#include "Database.h"
#include "ConditionList.h"
#include "Condition.h"
#include "Operation.h"
#include "Entry.h"

#include <iostream>
#include <sstream>
#include <vector>


class Parser{

	Database& database;

	//"views" are the temporary relations created by a program
	vector<Relation> views;

	void addView( Relation r ){
		views.push_back( r );
	}

	//Get a relation from views or database
	Relation getRelation( string r );

	//Is c alpha numeric or '_'?
	bool isAlphaNum( int c );

	//IO FUNCTIONS
	//These are functions which deal with files and commands have already been parsed for the most part

	//TODO
	int writeFile( string relationName );

	//TODO 
	//Opens a file by relation name, and parses all commands in file.
	int openFile( string relationName );

	//TODO
	//Close a file when done
	int closeFile( string relationName );

	//PARSER/STRINGSTREAM FUNCTIONS



	//COMMANDS
	//The command itself ("insert into", "create table", "delete from", "update") has already been read by the parser



	//TODO
	//Parse the rest of a create table command
	int createTable( stringstream& command );

	//TODO
	//Parse the rest of delete from command
	int deleteFrom( stringstream& command );

	//TODO
	//Parse the rest of insert into command
	int insertInto( stringstream& command );

	//TODO
	//Parse the rest of update command
	int update( stringstream& command );



	//QUERIES
	//The query command ("project", "select", "rename", etc.) has already been read by the parser


	//DONE (I think)
	Relation selection( stringstream& command );

	//DONE
	Relation projection( stringstream& command );

	//TODO
	Relation relationUnion( stringstream& command );

	//TODO
	Relation difference( stringstream& command );

	//TODO
	Relation crossProduct( stringstream& command );

	//DONE
	Relation rename( stringstream& command );



	//GENERAL PARSER FUNCTIONS


	//DONE
	//Reads an attribute list (comma seperated strings, surrounded by parentheses)
	int parseAttributeList( stringstream& command, vector<string>& attributeNames );

	//DONE
	//Peeks to see if next character is a plus sign;
	int peekAndReadAddition( stringstream& command );

	//DONE
	//Peeks to see if next character is a minus sign;
	int peekAndReadSubtraction( stringstream& command );

	//DONE
	//Peeks to see if next character is a * sign;
	int peekAndReadMultiplication( stringstream& command );

	//DONE
	//Reads in an arrow, "<-". Returns 1 for success, -1 for failure.
	int readArrow( stringstream& command );

	//DONE
	//reads a semicolon. Returns -1 if failed.
	int readSemi( stringstream& command );

	//DONE
	//Reads whitespace
	void readWhite( stringstream& command );

	//DONE
	//reads and returns an alphanumeric word from the stream. (a-z, A-Z, 0-9, _)
	//This function first reads through any whitespace and then stores the word
	string readAlphaNumWord( stringstream& command );

	int parseInteger( stringstream& command, int& i );

	//DONE
	int readOperator( stringstream& command, Operation& o ); // changes operator& to operation&

	//UNDER CONSTRUCTION
	//Read a single condition
	Condition parseCondition( stringstream& command );

	//UNDER CONSTRUCTION
	//takes in a stream which has been identified as a condition and returns the resulting condition list
	vector<Condition> parseConditions( stringstream& command );

	//DONE
	//takes in a stream which has been identified as a query and returns a relation
	//Return NULL if error.
	//OFTEN CALLED RECURSIVELY
	Relation parseExpr( stringstream& command );

	//DONE
	//Reads in a query - ie. "relationName" <- expr
	int parseQuery( stringstream& command );

	//DONE
	//takes in a stream which may be a command and updates information - returns -1 for error
	int parseCommand( stringstream& command );

public:

	Parser( Database& d ) : database( d ) {}

	int parse( string command );


};

#endif