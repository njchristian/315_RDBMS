#ifndef RELATION_H_
#define RELATION_H_

#include "Entry.h"
#include <vector>

class Relation{

	// Data Members
	string relationName;
	vector<Attribute> attributes;
	vector<vector<Entry>> table;

	vector<int> keys;

public:

	// Constructors
	Relation(string givenName, vector<Attribute> givenAttributes, vector<int> givenKeys)
		: relationName(givenName), attributes(givenAttributes), keys(givenKeys){}

	Relation( vector<Attribute> givenAttributes ) : attributes(givenAttributes) {}
		
	// Public Functions	
	
	void addRow(vector<Entry> newRow){
		table.push_back(newRow);
	}
		
	void changeAttributeName(int index, string newName){
		attributes.at(index) = newName;
	}

	vector<vector<Entry>> getAllEntries() { return table; }

	vector<string> getAttributes(){ return attributes; }

	string getName(){ return relationName; }

	vector<Entry> getRow(int index){ return table.at(index); }


};

#endif