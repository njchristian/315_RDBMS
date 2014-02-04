#ifndef RELATION_H_
#define RELATION_H_

#include "Entry.h"
#include <vector>

class Relation{

	string relationName;
	vector<Attribute> attributes;
	vector<vector<Entry>> table;

	vector<int> keys;

public:

	Relation(string givenName, vector<string> givenAttributes, vector<int> givenKeys)
		: relationName(givenName), attributes(givenAttributes), keys(givenKeys){}

	vector<string> getAttributes(){ return attributes; }
	vector<vector<Entry>> getAllEntries() { return table; }
	vector<Entry> getRow(int index){ return table.at(index); }

	void changeAttributeName(int index, string newName){
		attributes.at(index) = newName;
	}

	void addRow(vector<Entry> newRow){
		table.push_back(newRow);
	}



};

#endif