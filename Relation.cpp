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


// Empties all of the attributes, tuples and keys from the relation.
void Relation::clear( ){

	attributes.clear( );
	table.clear( );
	keys.clear( );

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
bool Relation::hasTuple( vector<Entry*> tuple ) {
	for ( int i = 0; i < table.size( ); ++i ) {
		
		bool currentTuple = true;

		/****************
		This checks through all the KEYS to see if the 
		tuples are the same.
		****************/
		for(int j = 0; j <keys.size(); j++){
			if(table.at(i).at(keys.at(j) ) != tuple.at(keys.at(j))){
				currentTuple = false;
			}
		}

		if(currentTuple){
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
Relation& Relation::operator=(Relation& b){

	relationName = b.getName();
	attributes = b.getAttributes();
	table = b.getAllEntries();

	keys = b.getKeys();

	return *this;

}


// Output operator
ostream& operator<<(ostream& os, Relation& a){

	os<<"Name: "<<a.getName()<<"\n\n";

	for(int i = 0; i < a.attributeSize(); ++i){

		os<<a.getAttributeNameAt(i)<<": ";

	}

	os<<"\n\n";

	for(int i = 0; i < a.getNumTuples(); i++){

		stringstream ss;
		string tempS;
		for(int j = 0; j < a.attributeSize(); j++){

			Entry* t = a.getEntry(i, j);
			if(t->isInt()){
				ss<<t->getEntryI();
			}else{
				ss<<t->getEntryVC();
			}

			ss>>tempS;
			os<<tempS<<' ';

			ss.clear();
		}
		os<<'\n';
	}

	return os;
}