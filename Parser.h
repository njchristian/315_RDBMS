#ifndef PARSER_H_
#define PARSER_H_

#include "Database.h"
#include "ConditionList.h"
#include "Condition.h"
#include "Operation.h"
#include "Entry.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define SUCCESS 1
#define INVALID -1
#define EXIT -2


class Parser{

	Database& database;
	vector<vector<string>>& result;

	//"views" are the temporary relations created by a program
	vector<Relation> views;

	void addView( Relation r ){
		views.push_back( r );
	}

	int deleteView( string relationName);
	

	//Is c alpha numeric or '_'?
	bool isAlphaNum( int c );

	bool isNum( int c );

	bool isAlpha( int c );

	//IO FUNCTIONS
	//These are functions which deal with files and commands have already been parsed for the most part

	//DONE
	int writeFile( string relationName );

	//DONE 
	//Opens a file by relation name, and parses all commands in file.
	int openFile( string relationName );

	//DONE
	//Close a file when done
	int closeFile( string relationName );

	//PARSER/STRINGSTREAM FUNCTIONS



	//COMMANDS
	//The command itself ("insert into", "create table", "delete from", "update") has already been read by the parser



	//Mostly done, needs finishing up and testing
	//Parse the rest of a create table command
	int createTable( stringstream& command );

	//DONE - not tested
	//Parse the rest of delete from command
	int deleteFrom( stringstream& command );

	//DONE - needs testing
	//Parse the rest of insert into command
	int insertInto( stringstream& command );

	//DONE - not tested
	//Parse the rest of update command
	int update( stringstream& command );



	//QUERIES
	//The query command ("project", "select", "rename", etc.) has already been read by the parser


	//DONE (I think)
	int selection( stringstream& command, Relation& rel );

	//DONE
	int projection( stringstream& command, Relation& r );

	//DONE
	int rename( stringstream& command, Relation& r );

	//GENERAL PARSER FUNCTIONS

	string myGetLine( stringstream& command );

	//DONE
	//Reads an attribute list (comma seperated strings, surrounded by parentheses)
	int parseAttributeList( stringstream& command, vector<string>& attributeNames );

	// UNDER CONSTRUCTION
	int parseTypedAttribute( stringstream& command, vector<Attribute>& attributeList );

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
	
	int readAlphaNumWordStartsAlpha( stringstream& command, string& result );

	string readWord( stringstream& command );

	//DONE - needs testing
	// reads and returns an entry for the insert into function, opening parenthesis
	// will already be consumed and this should not consume the closing parenthesis
	int readLiteral( stringstream& command, Entry& e );

	//DONE
	int parseInteger( stringstream& command, int& i );

	//DONE
	int readOperator( stringstream& command, Operation& o ); // changed operator& to operation&

	//DONE
	//This finds out what the next connector is. We give it a copy of the stringstream
	//so we don't have to worry about returning it to the original state
	int findConnector( stringstream& copy, Connector& c, int paren );

	//DONE
	//Read a single condition
	int parseCondition( stringstream& command, int paren, Condition& condition );

	//DONE
	//takes in a stream which has been identified as a condition and returns the resulting condition list
	int parseConditions( stringstream& command, vector<Condition>& conditions );

	//DONE
	//takes in a stream which has been identified as a query and returns a relation
	//Return NULL if error.
	//OFTEN CALLED RECURSIVELY
	int parseExpr( stringstream& command, Relation& rel );

	//DONE
	//Reads in a query - ie. "relationName" <- expr
	int parseQuery( stringstream& command );

	//DONE
	//takes in a stream which may be a command and updates information - returns -1 for error
	int parseCommand( stringstream& command );

public:

	Parser( Database& d, vector<vector<string>>& r ) : database( d ), result(r) {}

	int parse( string command );

	//Get a relation from views or database
	int getRelation( string r, Relation& target );

};

#endif