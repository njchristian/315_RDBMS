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
	// Constructor & Destructor
	Database( ) {}

	// Public Functions

	Entry accessAttribute( );

	Relation accessRelation( );

	Entry accessTuple( );

	//no idea what the arguments should be
	void addRelationToDatabase( string name, vector<Attribute> attributes, vector<int> keys );

	//void addAttributeToRelation(  );
	void addTupleToRelation( vector<Entry> tuple, string relationName );

	//cross product of two relations given their in index
	Relation crossProduct( Relation& relationA, Relation& relationB );

	//difference of two relations given their in index
	Relation differenceTwoRelation( Relation& relationA, Relation& relationB );

	int findAttribute( );

	int findRelationinDatabase( );

	int findTuple( );

	Relation naturalJoin( Relation& relationA, Relation& relationB );

	//returns a Relation of all entries in each of the attributes
	Relation projection( string relationName, vector<string> attributeNames );

	void removeTupleFromRelation(  );

	//renaming an attribute in a relation
	void renameAttributes( vector<string> newNames, Relation& correctRelation );

	//print the tuples that satisfy an condition
	Relation selection( vector<Condition>, string targetRelationName ); //i don't know how to pass an conidtion

	//union two Relation given their index in relations
	Relation unionTwoRelations( Relation& relationA, Relation& relationB );


};

#endif