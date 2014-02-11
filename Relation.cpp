#include "Relation.h"

// Copy constructor
Relation::Relation( Relation* r ){

	relationName = r->getName( );
	attributes = r->getAttributes( );

	for ( int i = 0; i < r->getNumTuples( ); i++ ){

		table.push_back( vector<Entry*>( ) );

		for ( int j = 0; j < r->attributeSize( ); j++ ){

			table.at( i ).push_back( new Entry( *r->getEntry( i, j ) ) );

		}

	}

}

// Functions

// Adds a tuple/row to the relation.
void Relation::addRow( vector<Entry*> rowToAdd ) {
	table.push_back( rowToAdd );
}

void Relation::deleteRow(int index){

	int count = 0;

	for(vector<vector<Entry*>>::iterator i = table.begin(); i != table.end(); i++){

		if(count == index){
			table.erase(i);
			return;
		}

		++count;
	}

	cout<<"Error in delete row";

}
// Empties all of the attributes, tuples and keys from the relation.
void Relation::clear( ){

	attributes.clear( );
	table.clear( );
	keys.clear( );

}


// Removes the specified tuple from the relation. Returns whether
// it removed it or not.
bool Relation::removeTuple( vector<Entry> tuple ) {
	bool isSame;
	unsigned i = 0;
	// find the tuple 
	for ( auto it = table.begin( ); it != table.end( ); ++it ) {
		isSame = false;
		for ( unsigned j = 0; j < it->size( ); ++j ) {
			if ( tuple[ j ] == *table[ i ][ j ] ) {
				isSame = true;
			}
		}
		// if tuple is found, delete it and return
		if ( isSame == true ) {
			table.erase( it );
			return true;
		}
		++i;
	}

	return false;
}


// Get the names of the relation's attributes.
vector<string> Relation::getAttributeNames(){

	vector<string> result;

	for (int i = 0; i < attributes.size(); i++){
		result.push_back(attributes.at(i).name);
	}

	return result;
}


// Check to see if a relation has the specified tuple in it already.
bool Relation::hasTuple( vector<Entry*> tuple ) const {
	for ( int i = 0; i < table.size( ); ++i ) {

		bool currentTuple = true;

		/****************
		This checks through all the KEYS to see if the
		tuples are the same.
		****************/

		for ( int j = 0; j < keys.size( ); j++ ){
			if ( table.at( i ).at( keys.at( j ) ) != tuple.at( keys.at( j ) ) ){
				currentTuple = false;
			}
		}

		if ( currentTuple ){
			return true;
		}

	}

	return false;
}


// Set the relation's attributes to the newly given ones.
void Relation::setAttributes( vector<Attribute> newAttributes ) { 
	attributes = newAttributes; 
}


// Rename the attributes in the relation.
void Relation::setAttributeNames( vector<string> newNames ) {
	// Error check
	if ( attributes.size( ) != newNames.size( ) ) {
		cout << "Error, tried to setAttributeNames but did not"
			 << " have the right number of names!\n";
	}
	
	// Set the new names.
	for ( unsigned i = 0; i < attributes.size( ); ++i ) {
		attributes[ i ].name = newNames[ i ];
	}
}


// Overloaded assignment operator.
Relation& Relation::operator=( Relation& b ){

	relationName = b.getName( );
	attributes = b.getAttributes( );
	table = b.getAllEntries( );

	keys = b.getKeys( );

	return *this;

}


bool operator==(Relation& relationA, Relation& relationB){
	// Check to see if name is the same
	if ( relationA.getName( ) != relationB.getName( ) ) {
		return false;
	}

	// Check for the same attributes
	if ( relationA.getAttributes( ) != relationB.getAttributes( ) ) {
		return false;
	}

	// Check for the same keys
	if ( relationA.getKeys( ) != relationB.getKeys( ) ) {
		return false;
	}

	// Check for number of rows
	if ( relationA.getNumTuples( ) != relationB.getNumTuples( ) ) {
		return false;
	}

	// Make sure each row exists in both relations
	for ( unsigned i = 0; i < relationB.getNumTuples( ); ++i ) {
		if ( !relationA.hasTuple( relationB.getRow( i ) ) ) {
			return false;
		}
	}

	return true;
}


// Output operator
ostream& operator<<( ostream& os, Relation& a ){

	os << "Name: " << a.getName( ) << "\n\n";

	for ( int i = 0; i < a.attributeSize( ); ++i ){

		os << a.getAttributeNameAt( i ) << ": ";

	}

	os << "\n\n";

	for ( int i = 0; i < a.getNumTuples( ); i++ ){

		stringstream ss;
		string tempS;
		for ( int j = 0; j < a.attributeSize( ); j++ ){

			Entry* t = a.getEntry( i, j );
			if ( t->isInt( ) ){
				ss << t->getEntryI( );
			}
			else{
				ss << t->getEntryVC( );
			}

			ss >> tempS;
			os << tempS << ' ';

			ss.clear( );
		}
		os << '\n';
	}

	return os;
}