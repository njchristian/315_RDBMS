#include "Database.h"

// Private Functions

Relation* Database::findRelation( string relationName ){

	Relation* foundRelation = NULL;
	int i;
	for( i=0; i<relations.size(); ++i ){
		if( relations[ i ].getName() == relationName ){
			foundRelation = &relations[ i ];
			break; //i hope there are no duplicates. is there a possibility for duplicates?
		}
	}
	
	return foundRelation;
	
}

// ---------------------------------------------------------------------------------------
// Public Functions

//
Entry Database::accessAttribute( ) {

	Entry entry; //attribute

	return entry;

}


//
Relation Database::accessRelation( ) {

	Relation relation;
	
	return relation;
}


//
Entry Database::accessTuple( ) {

	Entry entry;

	return entry;
}


//the parser passes this function a list of attributes (name and type)
void Database::addRelationToDatabase( vector<Attribute> attributes ) {
	
	relations.push_back(Relation(attributes));

}


// Add the row (which is a tuple) into the specified relation.
void Database::addTupleToRelation( vector<Entry> tuple, string relationName ) {

	// find the correct relation

	// push_back the tuple into it

}


//cross product of two relations given their in index
Relation Database::crossProduct( Relation& relationA, Relation& relationB ){

}


//difference of two relations given their in index
Relation Database::differenceTwoRelation( Relation& relationA, Relation& relationB ) {

}


// 	
int Database::findAttribute( ) {

	int index = 0;

	return index;
}


//
int Database::findTuple( ) {

	int index = 0;

	return index;

}


//subset of attributes in a relation
Relation Database::projection( string relationName, vector<string> attributeNames ) {

	//get types of attributes

	//create new relation with attribute names and types
	Relation createdRelation;
	
	
	// find relation returns a Relation pointer, does it need to change or this??
	Relation& r = findRelation(relationName);
	
	//go through row by row and add new tuples with target values
	


	

	return createdRelation;
}


//
void Database::removeRelation( Relation relationToRemove ) {

}


//
void Database::removeTupleFromRelation(  ) {

}


//renames the attributes of a relation
void Database::renameAttributes( vector<string> newNames, Relation& correctRelation ) {

}


//print the tuples that satisfy an condition
vector<Entry> Database::selection( /* need parameter(s) */ ) { //i don't know how to pass a condition

	vector<Entry> createdRelation;

	return createdRelation;
}


//union two Relation given their index in relations
Relation Database::unionTwoRelations( Relation& relationA, Relation& relationB ) {

}



