#ifndef DATABASE_H_
#define DATABASE_H_

#include "Relation.h"
#include "Attribute.h"
#include "Type.h"
#include <vector>

class Database {

	// Data Members
	vector<Relation> relations; //might need to be public

	// Private Functions
	Relation* findRelation( string relationName );

public:
	// Constructor & Destructor
	Database( ) {};
	~Database( ) {};

	// Public Functions

	Entry accessAttribute( );

	Relation accessRelation( );

	Entry accessTuple( );

	//no idea what the arguments should be
	void addRelationToDatabase( vector<Attribute> attributes );

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

	void removeRelation( Relation relationToRemove );

	void removeTupleFromRelation(  );

	//renaming an attribute in a relation
	void renameAttributes( vector<string> newNames, Relation& correctRelation );

	//print the tuples that satisfy an condition
	vector<Entry> selection( /* need parameter(s) */ ); //i don't know how to pass an conidtion

	//union two Relation given their index in relations
	Relation unionTwoRelations( Relation& relationA, Relation& relationB );


};

#endif