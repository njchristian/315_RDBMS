#include "Database.h"

Relation* Database::findRelation( string relationName ){

	Relation* foundRelation = NULL:
	int i;
	for( i=0; i<relations.size(); ++i ){
		if( relations[ i ].getName() == relationName ){
			foundRelation = relation[ i ];
			break; //i hope there are no duplicates
		}
	}
	
	return foundRelation;
	
}

//the parser passes this function a list of attributes (name and type)
void Database::addRelationToDatabase( vector<Attribute> attributes ) {
	
	relations.push_back(Relation(attributes));

}

void Database::addAttributeToRelation( Entry ) {

	
}

void Database::addTupleToRelation( vector<Entry> tuple, string relationName ) {

	

}

void Database::removeRelation( Relation ) {

}

void Database::removeAttributeFromRelation( Entry ) {

}

void Database::removeTupleFromAttribute( Entry ) {

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
Relation Database::projection( string relationName, vector<string> attributeNames ) {

	//get types of attributes

	//create new relation with attribute names and types
	Relation createdRelation(;
	
	
	
	Relation& r = findRelation(relationName);
	
	//go through row by row and add new tuples with target values
	


	

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