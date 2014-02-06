#ifndef DATABASE_H_
#define DATABASE_H_

#include "Relation.h"
#include "Attribute"
#include "Type.h"
#include <vector>

class Database{

	// Data Members
	vector<Relation> relations; //might need to be public

	// Private Functions
	Relation* findRelation(string relationName);

public:
	// Constructor & Destructor
	Database( ) { };
	~Database( ) { };

	// Public Functions

	Entry accessAttribute( );

	Relation accessRelation( );

	Entry accessTuple( );

	//no idea what the arguments should be
	void addRelationToDatabase(  );

	//void addAttributeToRelation(  );
	void addTupleToRelation(  );

	//cross product of two relations given their in index
	Relation crossProduct( Relation&, Relation& );

	//difference of two relations given their in index
	Relation differenceTwoRelation( Relation&, Relation& );

	int findAttribute( );

	int findRelationinDatabase( );

	int findTuple( );	

	Relation naturalJoin( Relation&, Relation& );

	//returns a Relation of all entries in each of the attributes
	Relation projection( string relationName, vector<string> attributeNames );

	void removeAttributeFromRelation(  );

	void removeRelation(  );

	void removeTupleFromRelation(  );

	//renaming an attribute in a relation
	void renameAttributes( vector<string>, Relation& );

	//print the tuples that satisfy an condition
	vector<Entry> selection(  ); //i don't know how to pass an conidtion

	//union two Relation given their index in relations
	Relation unionTwoRelations( Relation&, Relation& );		


};

#endif