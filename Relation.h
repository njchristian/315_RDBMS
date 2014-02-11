#ifndef RELATION_H_
#define RELATION_H_

#include "Entry.h"
#include "Attribute.h"
#include "Condition.h"
#include <sstream>
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

	Relation( Relation* r );

	// Public Functions	
	void addRow( vector<Entry*> rowToAdd );

	int attributeSize( ){ return attributes.size( ); }

	void changeAttributeName( int index, string newName ){
		attributes.at( index ).name = newName;
	}

	void clear( );

	vector<Attribute> getAttributes( ){ return attributes; }

	vector<Attribute>* getAttributesPointer( ) { return &attributes; }

	Attribute getAttributeAt(int i) { return attributes.at(i); }

	vector<string> Relation::getAttributeNames( );
	
	string getAttributeNameAt( int i ){ return attributes.at( i ).name; }

	vector<vector<Entry*>> getAllEntries() { return table; }	

	bool removeTuple( vector<Entry> tuple );
	
	Entry* getEntry( int i, int j ){ return table.at( i ).at( j ); }

	vector<int> getKeys( ) { return keys; }

	string getName(){ return relationName; }
	
	int getNumTuples(){ return table.size(); }

	vector<Entry*> getRow( int index ){ return table.at( index ); }

	bool hasTuple( vector<Entry*> tuple );

	void setAttributes( vector<Attribute> newAttributes );

	void setAttributeNames( vector<string> newNames );

	void setName( string n ){ relationName = n; }

	void setTable( vector<vector<Entry*> > newTable ) { table = newTable;  }

	void update( string attributeName, string testCondition, Operation op, Entry newValue );

	Relation& operator=(Relation& b);

	
};

bool operator==( Relation& relationA, Relation& relationB );

ostream& operator<<(ostream& os, Relation& a);

#endif