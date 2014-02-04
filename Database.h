#ifndef DATABASE_H_
#define DATABASE_H_

#include "Relation.h"
#include "Attribute"
#include "Type.h"
#include <vector>

class Database{

	vector<Relation> relations; //might need to be public

	Relation& findRelation(string relationName);

public:
	Database( ) { };
	~Database( ) { };

	//no idea what the arguments should be
	void addRelationToDatabase(  );
	//void addAttributeToRelation(  );
	void addTupleToRelation(  );

	void removeRelation(  );
	void removeAttributeFromRelation(  );
	void removeTupleFromRelation(  );

	int findRelationinDatabase( );
	Relation accessRelation( );

	int findAttribute( );
	Entry accessAttribute( );

	int findTuple( );
	Entry accessTuple( );

	//print the tuples that satisfy an condition
	vector<Entry> selection(  ); //i don't know how to pass an conidtion

	//returns a Relation of all entries in each of the attributes
	Relation projection( string relationName, vector<string> attributeNames );

	//renaming an attribute in a relation
	void renameAttributes( vector<string>, Relation& );

	//union two Relation given their index in relations
	Relation unionTwoRelations( Relation&, Relation& );

	//difference of two relations given their in index
	Relation differenceTwoRelation( Relation&, Relation& );

	//cross product of two relations given their in index
	Relation crossProduct( Relation&, Relation& );
	
	Relation naturalJoin( Relation&, Relation& );


};

#endif