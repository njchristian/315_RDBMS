#ifndef DATABASE_H_
#define DATABASE_H_

#include "Relation.h"
#include "Attribute.h"
#include "Type.h"
#include "ConditionList.h"
#include "Condition.h"
#include <vector>

class Database {

	//It might be useful to have a relation which we use to store results
	Relation result;

	// Data Members
	vector<Relation*> relations; //might need to be public

	// Private Functions
	Relation* findRelation( string relationName );

public:
	// Constructor
	Database( ) { }

	// Public Functions

	Entry accessAttribute( );

	Relation* accessRelation( string name );

	Entry accessTuple( );

	void addRelationToDatabase( string name, vector<Attribute> attributes, 
		vector<int> keys );

	void addTupleToRelation( vector<Entry> tuple, string relationName );

	Relation crossProduct( string relationAName, string relationBName );

	Relation differenceTwoRelation( string relationAName, string relationBName );

	int findAttribute( );

	int findRelationinDatabase( );

	int findTuple( );

	Relation naturalJoin( string relationA, string relationB );

	Relation projection( string relationName, vector<string> attributeNames );

	void removeTupleFromRelation( );

	Relation renameAttributes( vector<string> newNames, string relationName );

	Relation selection( vector<Condition>, string targetRelationName );

	Relation unionTwoRelations( string rA, string rB );

};

#endif