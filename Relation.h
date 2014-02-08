#ifndef RELATION_H_
#define RELATION_H_

#include "Entry.h"
#include "Attribute.h"
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
	Relation() {}

	Relation(string givenName, vector<Attribute> givenAttributes, vector<int> givenKeys)
		: relationName(givenName), attributes(givenAttributes), keys(givenKeys){}

	Relation( vector<Attribute> givenAttributes ) : attributes(givenAttributes) {}

	Relation(Relation* r){

		relationName = r->getName();
		attributes = r->getAttributes();

		for(int i = 0; i < r->getNumTuples(); i++){

			table.push_back(vector<Entry*>());

			for(int j = 0; j < r->attributeSize(); j++){

				table.at(i).push_back(new Entry(*r->getEntry(i, j)));

			}

		}

	}

	// Public Functions	

	void setName(string n){ relationName = n; }
	
	void addRow(vector<Entry*> newRow){
		table.push_back(newRow);
	}
		
	void changeAttributeName(int index, string newName){
		attributes.at(index).name = newName;
	}
	void setAttributes(vector<Attribute> a){
		attributes = a;
	}


	vector<vector<Entry*>> getAllEntries() { return table; }
	vector<Attribute> getAttributes(){ return attributes; }

	vector<string> getAttributeNames();

	vector<int> getKeys(){ return keys; }

	string getName(){ return relationName; }
	string getAttributeNameAt(int i){ return attributes.at(i).name;}
	
	int attributeSize(){ 
		return attributes.size(); 
	}
	int getNumTuples(){ return table.size(); }
	
	vector<Entry*> getRow(int index){ return table.at(index); }

	Entry* getEntry(int i, int j){ return table.at(i).at(j); }

	void clear();
	
	bool hasTuple( vector<Entry*> tuple );

	Relation& operator=(Relation& b);

	
};

ostream& operator<<(ostream& os, Relation& a);

#endif