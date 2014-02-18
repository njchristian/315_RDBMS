#include "Database.h"
#include <iostream>
#include <algorithm>

// Private Functions

// Returns a pointer to the relation that has the specified name. 
Relation* Database::findRelation( string relationName ) {

	Relation* foundRelation;
	unsigned int i;
	for( i = 0; i < relations.size( ); ++i ) {
		if( relations[ i ]->getName( ) == relationName ) {
			foundRelation = relations[ i ];
			return foundRelation; 
			break; 
		}
	}
	return NULL;
}


// ----------------------------------------------------------------------------
// Public Functions

//
Attribute* Database::accessAttribute( string name , string relationName ) {

	Relation* relation = findRelation(relationName);
	vector<Attribute>* attributes = relation->getAttributesPointer();

	Attribute* attrib = NULL;

	unsigned int i;
	for( i = 0; i < attributes->size(); ++i ){
		if( attributes->at(i).name == name ){
			attrib = &attributes->at(i);
			break;
		}
	}


	return attrib;

}


// Returns a pointer to the relation with the specified name.
Relation Database::accessRelation( string name ) {
	
	Relation* r = findRelation(name);

	if( r == NULL ){
		return Relation();
	}

	return *r;
}

Relation* Database::accessRelationPointer( string name ){

	return findRelation(name);

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

void Database::addRelationToDatabase( Relation r ){

	Relation* newRelation = new Relation(r);
	
	relations.push_back(newRelation);

}

// Add the row (which is a tuple) into the specified relation.
void Database::addTupleToRelation( vector<Entry> tuple, Relation* targetRelation ) {

	//Relation* targetRelation = findRelation( relationName );

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

Relation Database::deleteFromRelation( Relation* targetRelation, vector<Condition> conditions ){

	ConditionList cl = ConditionList( conditions, targetRelation );

	//WE CANT DELETE THESE RIGHT AWAY OR ELSE WE MESS UP OUR DATA STRUCTURES
	vector<int> toBeDeleted;

	for ( int i = 0; i < targetRelation->getNumTuples( ); ++i ){

		if ( cl.evalOnTuple( i ) ){
			toBeDeleted.push_back( i );
		}

	}

	for ( unsigned i = 0; i < toBeDeleted.size( ); i++ ){

		//the index decreases as we delete rows
		targetRelation->deleteRow( toBeDeleted.at( i ) - i );

	}

	return targetRelation;
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


int Database::findCorrespondingRow( vector<Entry*> rowA, 
	vector<int> indexA, Relation* b, vector<int> indexB ){

	vector<vector<Entry*>> tableB = b->getAllEntries( );

	for ( unsigned i = 0; i < tableB.size( ); i++ ){

		bool flag = true;

		for ( unsigned j = 0; j < indexB.size( ); j++ ){



			for ( unsigned k = 0; k < indexA.size( ); k++ ){


				if ( *( rowA.at( indexA.at( k ) ) ) != *( 
					tableB.at( i ).at( indexB.at( j ) ) ) ){
					
					flag = false;
				}

			}

		}

		if ( flag ){
			return i;
		}

	}
	return 0;
}


//
int Database::findTuple( ) {

	int index = 0;

	return index;

}

Relation* Database::insertIntoFromRelation( Relation* relationA, Relation* relationB ){

	//Relation* targetRelation = findRelation( relationA );

	if ( relationA->attributeSize( ) != relationB->attributeSize( ) ){
		return relationA;
	}

	for ( int i = 0; i < relationB->getNumTuples( ); i++ ){

		vector<Entry*> newRow = relationB->getRow( i );

		relationA->addRow( newRow );

	}

	return relationA;
}

//subset of attributes in a relation
Relation Database::projection( vector<string> attributeNames,
	Relation* targetRelation ) {

	result.clear( );

	//get types of attributes

	vector<int> attributeIndeces;

	for ( int i = 0; i < targetRelation->attributeSize( ); ++i ){

		for ( unsigned j = 0; j < attributeNames.size( ); ++j ){

			if ( attributeNames.at( j ) == targetRelation->getAttributeNameAt( i ) ) {
				attributeIndeces.push_back( i );
			}

		}

	}

	//SET ATTRIBUTE VECTOR FOR RESULT 

	vector<Attribute> resultAtts;

	for ( unsigned i = 0; i < attributeIndeces.size( ); ++i ){

		resultAtts.push_back( targetRelation->getAttributeAt( attributeIndeces.at( i ) ) );

	}

	result.setAttributes( resultAtts );

	//go through row by row and add new tuples with target values

	for ( int i = 0; i < targetRelation->getNumTuples( ); ++i ){

		vector<Entry*> newRow;

		for ( unsigned j = 0; j < attributeIndeces.size( ); ++j ){

			newRow.push_back( targetRelation->getEntry( i, attributeIndeces.at( j ) ) );

		}

		result.addRow( newRow );
	}



	return result;
}


void Database::removeRelationFromDatabase( string relationName ) {
	Relation* targetRelation = findRelation( relationName );

	// Iterator through the vector of the relations until the correct one is
	// found and then erase it.
	for ( auto iterator = relations.begin( ); iterator != relations.end( ); ++iterator ) {
		if ( *iterator == targetRelation ) {
			relations.erase( iterator );
			break;
		}
	}
}


//
void Database::removeTupleFromRelation( vector<Entry> tuple, string relationName ) {
	Relation* targetRelation = findRelation( relationName );

	bool didRemove = targetRelation->removeTuple( tuple );

	if ( didRemove == true ) {
		cout << "Tuple removed successfully.\n";
	}
	else {
		cout << "Tuple not found/removed from the relation.\n";
	}
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

	result.clear( );

	// Set up the list of conditions.
	ConditionList cl = ConditionList( conditions, targetRelation );

	// Find the tuples in the relation that satisfy the conditions and add
	// them to the new relation.
	for ( int i = 0; i < targetRelation->getNumTuples( ); i++ ){
		if ( cl.evalOnTuple( i ) ){

			vector<Entry*> newRow;

			// Find the columns that satify the conditions and create
			// a tuple out of them
			for ( int j = 0; j < targetRelation->attributeSize( ); j++ ){

				newRow.push_back( new Entry( *targetRelation->getRow( i ).at( j ) ) );

			}

			// Add the newly created tuple to the new relation.
			result.addRow( newRow );
		}

	}

	result.setAttributes( targetRelation->getAttributes( ) );

	result.setKeys( targetRelation->getKeys() );

	return result;
}


// Find the union two Relations given their names. The union of the two
// is then returned and stored in the result data member.
Relation Database::unionTwoRelations( Relation* relationA, Relation* relationB ) {

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

	// Add the tuples from relationB to the new relation that do not already
	// exist in it.
	// --------------------------------------------------------------Does it need to remove duplicates??
	for ( int i = 0; i < relationB->getNumTuples( ); i++ ){
		if ( !result.hasTuple( relationB->getRow( i ) ) ) {
			result.addRow( relationB->getRow( i ) );
		}
	}

	return result;
}

Relation Database::naturalJoin( Relation* relationA, Relation* relationB )
{

	Relation myResult;

	vector<Attribute> attA = relationA->getAttributes( );
	vector<Attribute> attB = relationB->getAttributes( );
	vector<Attribute> jointAttributes;
	vector<int> indexInA;
	vector<int> indexInB;
	vector<int> indexAOnly;
	vector<int> indexBOnly;

	//find the different of attributes of relationB
	//then project that new relation

	for ( unsigned i = 0; i < attA.size( ); i++ ){

		bool found = false;

		for ( unsigned j = 0; j < attB.size( ); j++ ){

			if ( attA.at( i ) == attB.at( j ) ){
				found = true;
				jointAttributes.push_back( attA.at( i ) );
				indexInA.push_back( i );
				indexInB.push_back( j );
			}
		}

		if ( !found ){
			indexAOnly.push_back( i );
		}

	}



	for ( unsigned i = 0; i < attB.size( ); i++ ){

		bool found = false;

		for ( unsigned j = 0; j < attA.size( ); j++ ){
			if ( attB.at( i ) == attA.at( j ) ){
				found = true;
			}
		}

		if ( !found ){
			indexBOnly.push_back( i );
		}

	}

	vector<Attribute> rA;
	for ( unsigned i = 0; i < indexAOnly.size( ); i++ ){
		rA.push_back( attA.at( indexAOnly.at( i ) ) );
	}

	for ( unsigned i = 0; i < jointAttributes.size( ); i++ ){
		rA.push_back( jointAttributes.at( i ) );
	}

	for ( unsigned i = 0; i < indexBOnly.size( ); i++ ){
		rA.push_back( attB.at( indexBOnly.at( i ) ) );
	}

	myResult.setAttributes( rA );

	vector<Relation> aOnly;
	vector<Relation> bOnly;
	vector<Relation> shared;

	for ( unsigned i = 0; i < indexAOnly.size( ); i++ ){
		vector<string> att;
		att.push_back( relationA->getAttributeAt( indexAOnly.at( i ) ).name );

		aOnly.push_back( projection( att, relationA ) );

	}

	for ( unsigned i = 0; i < indexInA.size( ); i++ ){
		vector<string> att;
		att.push_back( relationA->getAttributeAt( indexInA.at( i ) ).name );

		shared.push_back( projection( att, relationA ) );

	}

	for ( unsigned i = 0; i < indexBOnly.size( ); i++ ){
		vector<string> att;
		att.push_back( relationB->getAttributeAt( indexBOnly.at( i ) ).name );

		bOnly.push_back( projection( att, relationB ) );

	}

	int numRows = relationA->getNumTuples( );

	for ( int i = 0; i < numRows; i++ ){

		vector<Entry*> newRow;

		for ( unsigned j = 0; j < aOnly.size( ); j++ ){

			newRow.push_back( aOnly.at( j ).getEntry( i, 0 ) );

		}

		for ( unsigned j = 0; j < shared.size( ); j++ ){

			newRow.push_back( shared.at( j ).getEntry( i, 0 ) );

		}

		int row = findCorrespondingRow( relationA->getRow( i ), indexInA, relationB, indexInB );

		for ( unsigned j = 0; j < bOnly.size( ); j++ ){

			newRow.push_back( bOnly.at( j ).getEntry( row, 0 ) );

		}

		myResult.addRow( newRow );

	}

	result = myResult;

	return result;
}



// Updates all of the entries in a relation that meet the specified condition
Relation* Database::update( string relationName, vector<string> attributeNames,
	vector<Entry> newVals, vector<Condition> conditions ) {

	Relation* targetRelation = findRelation( relationName );

	vector<string> targetAttNames = targetRelation->getAttributeNames( );

	vector<int> targetIndeces;

	for ( unsigned i = 0; i < attributeNames.size( ); i++ ){

		for ( unsigned j = 0; j < targetAttNames.size( ); j++ ){

			if ( attributeNames.at( i ) == targetAttNames.at( j ) ){
				targetIndeces.push_back( j );
			}

		}

	}

	ConditionList cl = ConditionList( conditions, targetRelation );

	for ( int i = 0; i < targetRelation->getNumTuples( ); i++ ){

		if ( cl.evalOnTuple( i ) ){

			vector<Entry*> targetRow = targetRelation->getRow( i );

			for ( unsigned j = 0; j < targetIndeces.size( ); j++ ){

				delete targetRow.at( targetIndeces.at( j ) );
				targetRow.at( targetIndeces.at( j ) ) = new Entry( newVals.at( j ) );

			}

			targetRelation->updateRow( targetRow, i );

		}

	}

	return targetRelation;
}
