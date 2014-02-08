#include "Database.h"
#include <iostream>

// Private Functions

Relation* Database::findRelation( string relationName ){

	Relation* foundRelation;
	int i;
	for( i=0; i<relations.size(); ++i ){
		if( relations[ i ]->getName() == relationName ){
			foundRelation = relations[ i ];
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
void Database::addRelationToDatabase( string name, vector<Attribute> attributes, vector<int> keys ) {
	
	Relation* newRelation = new Relation(name, attributes, keys);

	relations.push_back(newRelation);

}


// Add the row (which is a tuple) into the specified relation.
void Database::addTupleToRelation( vector<Entry> tuple, string relationName ) {

	Relation* targetRelation = findRelation(relationName);

	vector<Entry*> newRow;

	for(int i = 0; i < tuple.size(); i++){
		newRow.push_back(new Entry(tuple.at(i)));
	}

	targetRelation->addRow(newRow);

}


//cross product of two relations given their in index
Relation Database::crossProduct( Relation& relationA, Relation& relationB ){
	return result;
}


//difference of two relations given their in index
Relation Database::differenceTwoRelation( Relation& relationA, Relation& relationB ) {

	return result;
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
	Relation* r = findRelation(relationName);
	
	//go through row by row and add new tuples with target values
	


	

	return createdRelation;
}


//
void Database::removeTupleFromRelation(  ) {

}


//renames the attributes of a relation
void Database::renameAttributes( vector<string> newNames, Relation& correctRelation ) {

}


//COMPLETE

//Return a relation of tuples that satisfy the conditions
Relation Database::selection( vector<Condition> conditions, string targetRelationName ) {

	Relation* targetRelation = findRelation(targetRelationName);

	result.clear();

	ConditionList cl = ConditionList(conditions, targetRelation);

	for(int i = 0; i < targetRelation->getNumTuples(); i++){

		if( cl.evalOnTuple(i) ){

			vector<Entry*> newRow;

			for(int j = 0; j < targetRelation->attributeSize(); j++){
				
				newRow.push_back(new Entry(*targetRelation->getRow(i).at(j)));
				
			}

			result.addRow( newRow );
		}

	}

	result.setAttributes( targetRelation->getAttributes() );

	return result;
}


//union two Relation given their index in relations
Relation Database::unionTwoRelations( string rA, string rB ) {

	Relation* relationA = findRelation(rA);
	Relation* relationB = findRelation(rB);

	result.clear();

	vector<Attribute> attA = relationA->getAttributes();
	vector<Attribute> attB = relationB->getAttributes();

	//If not same size, return empty
	if(attA.size() != attB.size()){
		return result;
	}

	for(int i = 0; i < attA.size(); i++){

		//if any attribute different, return empty
		if(attA.at(i).name != attB.at(i).name || attA.at(i).t != attB.at(i).t){
			return result;
		}

	}
	
	result = *relationA;

	for(int i = 0; i < relationB->getNumTuples(); i++){

		result.addRow(relationB->getRow(i));

	}

	return result;
}


