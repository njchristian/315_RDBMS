#ifndef DATABASE_H_
#define DATABASE_H_

#include "Relation.h"
#include "Type.h"
#include <vector>

class Database{

	vector<Relation> relations; //might need to be public



public:
	Database( ) { };
	~Database( ) { };

	//no idea what the arguments should be
	void addRelationToDatabase(  );
	void addAttributeToRelation( );
	void addTupleToAttribute(  );

	void removeRelation(  );
	void removeAttributeFromRelation(  );
	void removeTupleFromAttribute( );

	int findRelationinDatabase( );
	Relation accessRelation( );

	int findAttribute( );
	Entry accessAttribute( );

	int findTuple( );
	Entry accessTuple( );

	//print the tuples that satisfy an condition
	vector<Entry> selection(  ); //i don't know how to pass an conidtion

	//subset of attributes in a relation
	vector<Entry> projection( );

	//renaming an attribute in a relation
	void renamingAnAttribute( );

	//union two Relation given their index in relations
	void unionTwoRelations( int relationA, int relationB );

	//difference of two relations given their in index
	void differenceTwoRelation( int relationA, int relationB );

	//cross product of two relations given their in index
	void crossProduct( int relationA, int relationB );


};

#endif