#ifndef ENTRY_H_
#define ENTRY_H_

#include "Type.h"
#include <iostream>
#include <string>

using namespace std;

class Entry{

	// Data Members
	Type t;
	int intEntry;
	string vcEntry;

public:

	// Constructors
	Entry(){}
	Entry(int givenInt) : intEntry(givenInt) {
		t = INTEGER;
	}
	Entry(string givenVC) : vcEntry(givenVC) {
		t = VARCHAR;
	}

	// Public Functions
	bool isInt(){
		return t==INTEGER;
	}

	int getEntryI(){
		return intEntry;
	}

	Type getEntryType(){
		return t;
	}

	string getEntryVC(){
		return vcEntry;
	}

};

#endif