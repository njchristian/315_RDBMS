#ifndef RELATION_H_
#define RELATION_H_

#include "Entry.h"
#include "Attribute.h"
#include <vector>

class Relation{

	// Data Members
	string relationName;
	vector<Attribute> attributes;
	vector<vector<Entry*>> table;

	vector<int> keys;

public:

	// Constructors
	Relation( ) {}

	Relation( string givenName, vector<Attribute> givenAttributes, vector<int> givenKeys )
		: relationName( givenName ), attributes( givenAttributes ), keys( givenKeys ){}

	Relation( vector<Attribute> givenAttributes ) : attributes( givenAttributes ) {}

	// Public Functions	

	void addRow( vector<Entry*> newRow ){
		table.push_back( newRow );
	}

	void changeAttributeName( int index, string newName ){
		attributes.at( index ).name = newName;
	}

	vector<vector<Entry*>> getAllEntries( ) { return table; }

	vector<Attribute> getAttributes( ) { return attributes;  }
	//vector<string> getAttributes();

	string getName( ){ return relationName; }
	string getAttributeNameAt( int i ){ return attributes.at( i ).name; }

	int attributeSize( ){ return attributes.size( ); }
	int getNumTubles( ){ return attributes.size( ); }

	vector<Entry*> getRow( int index ){ return table.at( index ); }

	Entry* getEntry( int i, int j ){ return table.at( i ).at( j ); }

	bool hasTuple( vector<Entry*> tuple );

	void clear( );

	void setAttributes( vector<Attribute> newAttributes ) { attributes = newAttributes; }

};

#endif