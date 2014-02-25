#include "Relation.h"

// Copy constructor
Relation::Relation( Relation* r ) {

	relationName = r->getName( );
	attributes = r->getAttributes( );

	for ( int i = 0; i < r->getNumTuples( ); i++ ) {

		table.push_back( vector<Entry*>( ) );

		for ( int j = 0; j < r->attributeSize( ); j++ ) {

			table.at( i ).push_back( new Entry( *r->getEntry( i, j ) ) );

		}

	}

}

// Functions

// Adds a tuple/row to the relation.
void Relation::addRow( vector<Entry*> rowToAdd ) {
	table.push_back( rowToAdd );
}


// delete a row of the relation table
void Relation::deleteRow( int index ) {

	int count = 0;

	for ( vector<vector<Entry*>>::iterator i = table.begin( ); i != table.end( ); i++ ) {

		if ( count == index ) {
			table.erase( i );
			return;
		}

		++count;
	}

	cout << "Error in delete row";

}


// Empties all of the attributes, tuples and keys from the relation.
void Relation::clear( ){

	attributes.clear( );
	table.clear( );
	keys.clear( );

}


string evalStrLength( string target, int TBL_ENTRY ) {

	if ( target.size( )<TBL_ENTRY ) {
		return target;
	}

	string result = "";

	//The minus 5 reduces as follows - 3 for the "..." and the extra 2 for appropiate spacing
	for ( int i = 0; i < TBL_ENTRY - 5; i++ ) {
		result = result + target.at( i );
	}

	result = result + "...";

	return result;

}


// Get the names of the relation's attributes.
vector<string> Relation::getAttributeNames( ) {

	vector<string> result;

	for ( int i = 0; i < attributes.size( ); i++ ) {
		result.push_back( attributes.at( i ).name );
	}

	return result;
}


// Check to see if a relation has the specified tuple in it already.
bool Relation::hasTuple( vector<Entry*> tuple ) {

	for ( int i = 0; i < table.size( ); ++i ) {

		bool currentTuple = true;

		/****************
		This checks through all the KEYS to see if the
		tuples are the same.
		****************/
		for ( int j = 0; j < keys.size( ); j++ ) {
			if ( *table.at( i ).at( keys.at( j ) ) != *tuple.at( keys.at( j ) ) ) {
				currentTuple = false;
			}
		}

		if ( currentTuple ) {
			return true;
		}

	}

	return false;
}


// Check to see if a relation has the specified tuple in it already.
bool Relation::hasTuple( vector<Entry> tuple ) {

	for ( int i = 0; i < table.size( ); ++i ) {

		bool currentTuple = true;

		/****************
		This checks through all the KEYS to see if the
		tuples are the same.
		****************/
		for ( int j = 0; j < keys.size( ); j++ ) {
			if ( *table.at( i ).at( keys.at( j ) ) != tuple.at( keys.at( j ) ) ) {
				currentTuple = false;
			}
		}

		if ( currentTuple ) {
			return true;
		}

	}

	return false;
}


// check to see if the relation has the attribute 
// the string is the attribute name
bool Relation::hasAttribute( string s ) {

	for ( int i = 0; i < attributes.size( ); ++i ) {

		if ( attributes.at( i ).name == s ) {
			return true;
		}

	}

	return false;
}


// check to see if the relation is empty
bool Relation::isEmpty( ) {

	if ( table.size( ) > 0 ) {
		return false;
	}

	if ( attributes.size( ) != 0 ) {
		return false;
	}

	if ( relationName != "" ) {
		return false;
	}

	return true;

}


// remove the tuple from the relation
bool Relation::removeTuple( vector<Entry> tuple ) {
	bool isSame;
	unsigned i = 0;
	for ( auto it = table.begin( ); it != table.end( ); ++it ) {
		isSame = false;
		for ( unsigned j = 0; j < it->size( ); ++j ) {
			if ( tuple[ j ] == *table[ i ][ j ] ) {
				isSame = true;
			}
		}
		if ( isSame == true ) {
			table.erase( it );
			return true;
		}
		++i;
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
Relation& Relation::operator=( Relation& b ) {

	relationName = b.getName( );
	attributes = b.getAttributes( );
	table = b.getAllEntries( );

	keys = b.getKeys( );

	return *this;

}


bool operator==( Relation& relationA, Relation& relationB ) {

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
ostream& operator<<(ostream& os, Relation& a){

	//assume all ints have a max length of 12 (encompasses most all types of numbers
	int INTSIZE = 12;
	vector<Attribute> att = a.getAttributes();
	int entries = att.size();
	int WINDOWSIZE = 80;
	int MAXSIZE = WINDOWSIZE/ (entries + 1);

	int max = 0;

	for(int i = 0; i < att.size(); ++i){
		if(att.at(i).hasSize){

			if(att.at(i).vcSize > max){
				max = att.at(i).vcSize;

				if( max > MAXSIZE ){
					max = MAXSIZE;
					break;
				}
				
			}

		}else{
			
			if( INTSIZE > max ){
				max = INTSIZE;
			}

		}
	}

	os<<"\n\nRelation Name: "<<a.getName()<<"\n\n";

	for(int i = 0; i < a.attributeSize(); ++i){

		os<<setw(max)<<evalStrLength( a.getAttributeNameAt(i), max );

	}

	os<<"\n-------------------------------------------------------------------------------\n";

	for(int i = 0; i < a.getNumTuples(); i++){

		
		string tempS;
		for(int j = 0; j < a.attributeSize(); j++){

			stringstream ss;

			Entry* t = a.getEntry(i, j);
			if(t->isInt()){
				ss<<t->getEntryI();
			}else{
				ss<<t->getEntryVC();
			}

			tempS = ss.str();
			os<<setw(max)<<evalStrLength( tempS, max );

			ss.clear();
		}
		os<<'\n';
	}

	return os;
}
