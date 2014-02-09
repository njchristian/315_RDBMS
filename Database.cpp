#include "Database.h"
#include <iostream>
#include <algorithm>

// Private Functions

Relation* Database::findRelation( string relationName ){

	Relation* foundRelation;
	unsigned int i;
	for( i=0; i<relations.size(); ++i ){
		if( relations[ i ]->getName() == relationName ){
			foundRelation = relations[ i ];
			return foundRelation; // added this so it would compile -Taylor
			break; //i hope there are no duplicates. is there a possibility for duplicates?
		}
	}
	return &result;
}


// ---------------------------------------------------------------------------------------
// Public Functions

//
Entry Database::accessAttribute( ) {

	Entry entry; //attribute

	return entry;

}


// Returns a pointer to the relation with the specified name.
Relation* Database::accessRelation( string name ) {

	return findRelation( name );
}


//
Entry Database::accessTuple( ) {

	Entry entry;

	return entry;
}


// The parser passes this function a list of attributes (name and type)
void Database::addRelationToDatabase( string name, vector<Attribute> attributes, 
	vector<int> keys ) {

	// Create the new relation.
	Relation* newRelation = new Relation(name, attributes, keys);

	// Add the relation to the database.
	relations.push_back( newRelation );

}


// Add the row (which is a tuple) into the specified relation.
void Database::addTupleToRelation( vector<Entry> tuple, string relationName ) {

	Relation* targetRelation = findRelation( relationName );

	// Create the new tuple
	vector<Entry*> newRow;

	for ( unsigned int i = 0; i < tuple.size( ); i++ ) {
		newRow.push_back( new Entry( tuple.at( i ) ) );
	}

	// Add the new tuple to the relation
	targetRelation->addRow( newRow );

}


// Find the cross product of two relations given their names.
// The new relation is stored in the result data member.
Relation Database::crossProduct( Relation* relationA, Relation* relationB ) {

	result.clear( );

	// Create a vector for the attributes of both A and B and add all of the 
	// attributes to it.
	vector<Attribute> totalAttributes = relationA->getAttributes( );
	vector<Attribute> attributesOfB = relationB->getAttributes( );
	for ( unsigned i = 0; i < attributesOfB.size( ); ++i ) {
		totalAttributes.push_back( attributesOfB[ i ] );
	}

	// set the new attributes
	result.setAttributes( totalAttributes );

	vector<vector<Entry*> > relationATuples = relationA->getAllEntries( );
	vector<vector<Entry*> > relationBTuples = relationB->getAllEntries( );
	vector<vector<Entry*> > newRelationTuples;

	vector<Entry*> row;

	// Create the new tuples using the definition of cross product
	for ( unsigned i = 0; i < relationATuples.size( ); ++i ) {
		for ( unsigned j = 0; j < relationBTuples.size( ); ++j ) {
			row = relationATuples[ i ];
			row.insert( row.end( ), relationBTuples[ j ].begin( ), 
				relationBTuples[ j ].end( ) );
			newRelationTuples.push_back( row );
		}
	}

	// Add the new tuples to the relation
	result.setTable( newRelationTuples );
	
	return result;
}


// Find the difference of two relations given their names.
// Produces the set of tuples from the first that are not in the second
Relation Database::differenceTwoRelation( Relation* relationA, Relation* relationB ) {

	result.clear( );

	vector<Attribute> attributesOfA = relationA->getAttributes( );
	vector<Attribute> attributesOfB = relationB->getAttributes( );

	// Make sure that the relations are compatible
	if ( attributesOfA.size( ) != attributesOfB.size( ) ) {
		return result;
	}

	for ( unsigned i = 0; i < attributesOfA.size( ); ++i ) {
		if ( attributesOfA[ i ] != attributesOfB[ i ] ) {
			return result;
		}
	}

	result.setAttributes( relationA->getAttributes());

	// Find all of the tuples that are in A but not in B
	for ( int i = 0; i < relationA->getNumTuples( ); ++i ) {

		//if relationB does NOT have the tuple
		if ( !relationB->hasTuple( relationA->getRow( i ) ) ) {

			result.addRow( relationA->getRow( i ) );

		}

	}

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
Relation Database::projection( vector<string> attributeNames, Relation* targetRelation  ) {

	result.clear();

	//get types of attributes

	vector<int> attributeIndeces;

	for(int i = 0; i < targetRelation->attributeSize(); ++i){

		for(int j = 0; j <attributeNames.size(); ++j){

			if( attributeNames.at(j) == targetRelation->getAttributeNameAt(i) ){
				attributeIndeces.push_back(i);
			}

		}

	}

	//SET ATTRIBUTE VECTOR FOR RESULT 

	vector<Attribute> resultAtts;

	for(int i = 0; i < attributeIndeces.size(); ++i){

		resultAtts.push_back(targetRelation->getAttributeAt( attributeIndeces.at(i)));

	}

	result.setAttributes(resultAtts);

	//go through row by row and add new tuples with target values

	for(int i = 0; i < targetRelation->getNumTuples(); ++i){

		vector<Entry*> newRow;

		for(int j = 0; j < attributeIndeces.size(); ++j){

			newRow.push_back(targetRelation->getEntry(i, attributeIndeces.at(j)) );

		}

		result.addRow(newRow);
	}



	return result;
}


//
void Database::removeTupleFromRelation(  ) {

}


// Renames all of the attributes of a relation with the specified new names.
Relation Database::renameAttributes( vector<string> newNames, Relation* targetRelation ) {

	//Deep copy
	result = *targetRelation;

	result.setAttributeNames( newNames );

	return result;

}


//COMPLETE

// Return a relation of tuples that satisfy the conditions. The new relation 
// is stored in the result data member.
Relation Database::selection( vector<Condition> conditions, 
	Relation* targetRelation ) {

	result.clear();

	// Set up the list of conditions.
	ConditionList cl = ConditionList(conditions, targetRelation);

	// Find the tuples in the relation that satisfy the conditions and add
	// them to the new relation.
	for(int i = 0; i < targetRelation->getNumTuples(); i++){
		if( cl.evalOnTuple(i) ){

			vector<Entry*> newRow;

			// Find the columns that satify the conditions and create
			// a tuple out of them
			for(int j = 0; j < targetRelation->attributeSize(); j++){

				newRow.push_back(new Entry(*targetRelation->getRow(i).at(j)));

			}

			// Add the newly created tuple to the new relation.
			result.addRow( newRow );
		}

	}

	result.setAttributes( targetRelation->getAttributes() );

	return result;
}


// Find the union two Relations given their names. The union of the two
// is then returned and stored in the result data member.
Relation Database::unionTwoRelations( Relation* relationA, Relation* relationB ) {

	Relation* relationA = findRelation( rA );
	Relation* relationB = findRelation( rB );

	result.clear( );

	vector<Attribute> attA = relationA->getAttributes( );
	vector<Attribute> attB = relationB->getAttributes( );

	//If not same size, return empty
	if ( attA.size( ) != attB.size( ) ){
		return result;
	}

	for ( unsigned int i = 0; i < attA.size( ); i++ ){

		//if any attribute different, return empty
		if ( attA.at( i ).name != attB.at( i ).name || 
			 attA.at( i ).t != attB.at( i ).t ) {
			return result;
		}

	}

	// Set result to have relationA's tuples. This also sets up result's 
	// attributes and keys.
	// --------------------------------------------------------------Do we need to set a name for the new relation??
	result = *relationA;

	// Add the tuples from relationB to the new relation
	// --------------------------------------------------------------Does it need to remove duplicates??
	for(int i = 0; i < relationB->getNumTuples(); i++){
		result.addRow( relationB->getRow( i ) );

	}

	return result;
}

Relation Database::naturalJoin( Relation* relationA, Relation* relationB )
{

	result.clear( );

	vector<Attribute> attA = relationA->getAttributes( );
	vector<Attribute> attB = relationB->getAttributes( );
	vector<Attribute> joinAttribute;
	vector<int> indexInA;
	vector<int> indexInB;

	//find the different of attributes of relationB
	//then project that new relation

	sort(attA.begin(), attA.end(), Attribute::compareAttribute);
	sort(attB.begin(), attB.end(), Attribute::compareAttribute);

	//find the attributes in b and not in a
	vector<Attribute>::iterator it1 = attA.begin();
	vector<Attribute>::iterator it2 = attB.begin();

	while( it1 != attA.end() && it2 != attB.end() )
	{
		if( it1->name == it2->name )
		{
			//joinAttribute.push_back( *it1 );
			++it1;
			++it2;
		}
		else 
		{
			if( it1->name < it2->name )
			{
				++it1;
			}
			else 
			{
				joinAttribute.push_back( *it2 );
				++it2;
			}
			
		}
	}

	//place the rest into the vectors
	while( it1 != attA.end() )
	{
		++it1;
	}

	while( it2 != attB.end() )
	{
		joinAttribute.push_back( *it2 );
		++it2;
	}

	result.setAttributes( joinAttribute );

	result = projection( result.getAttributeNames(), relationB->getName() );

	//i was thinking cross product but that's not right
	//we need to map a row in relationA to a row in relationB
	result = crossProduct( relationA->getName(), result.getName() );

	return result;


}
