#ifndef DBCELL_H_
#define DBCELL_H_

#include "Parser.h"
#include "Database.h"

//FOR PART 2 WE DONT DEAL WITH THE DATABASE CELL
//THE DATABASE CELL IS THE GLUE BETWEEN THE PARSER AND THE DATABASE OBJECT
//IT IS ALSO WHAT THE USER SEES

class DBCell {

	// Data Members
	Parser* parser;
	Database database;
	vector<vector<string>>& result;

	//user defined relations
	vector<Relation> localRelations;

public:

	DBCell( vector<vector<string>>& r ) : result( r ) {
		parser = new Parser( database, result );
	}

	// Public Functions
	int execute( string dmlCommand ) {

		return parser->parse( dmlCommand );

	}

};

#endif