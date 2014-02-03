#include "Database.h"

void Database::addRelationToDatabase( Relation ) {

}

void Database::addAttributeToRelation( Entry ) {

}
void Database::addTupleToAttribute( Entry ) {

}

void Database::removeRelation( Relation ) {

}

void Database::removeAttributeFromRelation( Entry ) {

}

void Database::removeTupleFromAttribute( Entry ) {

}

int Database::findRelationinDatabase( ) {

	int index = 0;

	return index;
}

Relation Database::accessRelation( ) {

	Relation relation;
	
	return relation;
}
	
int Database::findAttribute( ) {

	int index = 0;

	return index;
}

Entry Database::accessAttribute( ) {

	Entry entry; //attribute

	return entry;

}

int Database::findTuple( ) {

	int index = 0;

	return index;

}

Entry Database::accessTuple( ) {

	Entry entry;

	return entry;
}
	
//print the tuples that satisfy an condition
vector<Entry> Database::selection( Condition ) { //i don't know how to pass an conidtion

	vector<Entry> createdRelation;

	return createdRelation;
}

//subset of attributes in a relation
vector<Entry> Database::projection( ) {

	vector<Entry> createdRelation;

	return createdRelation;
}


//renaming an attribute in a relation
void Database::renamingAnAttribute( ) {

}

//union two Relation given their index in relations
void Database::unionTwoRelations( int relationA, int relationB ) {

}

//difference of two relations given their in index
void Database::differenceTwoRelation( int relationA, int relationB ) {

}

//cross product of two relations given their in index
void Database::crossProduct( int relationA, int relationB ){

}