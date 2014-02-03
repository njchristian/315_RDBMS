#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>

using namespace std;
class Relation {};
class Entry {};
class Condition{};

class Database
{
public:
	Database( ) { };
	~Database( ) { };

	//no idea what the arguments should be
	void addRelationToDatabase( Relation );
	void addAttributeToRelation( Entry );
	void addTupleToAttribute( Entry );

	void removeRelation( Relation );
	void removeAttributeFromRelation( Entry );
	void removeTupleFromAttribute( Entry );

	int findRelationinDatabase( );
	Relation accessRelation( );
	
	int findAttribute( );
	Entry accessAttribute( );

	int findTuple( );
	Entry accessTuple( );
	
	//print the tuples that satisfy an condition
	vector<Entry> selection( Condition ); //i don't know how to pass an conidtion

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

private:
	vector<Relation> relations; //might need to be public

};


#endif