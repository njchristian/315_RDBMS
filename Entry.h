#ifndef ENTRY_H_
#define ENTRY_H_

#include "Type.h"
#include <iostream>
#include <string>

using namespace std;

class Entry{

	Type t;
	int intEntry;
	string vcEntry;

public:

	Entry(){}
	Entry(int givenInt) : intEntry(givenInt) {
		t = INTEGER;
	}
	Entry(string givenVC) : vcEntry(givenVC) {
		t = VARCHAR;
	}

	bool isInt(){
		return t==INTEGER;
	}

	int getEntryI(){
		return intEntry;
	}

	string getEntryVC(){
		return vcEntry;
	}

};

#endif