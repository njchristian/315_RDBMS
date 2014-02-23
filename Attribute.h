#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include "Type.h"
#include <string>

using namespace std;

struct Attribute{

	// Data members
	Type t;
	string name;
	int vcSize;
	bool hasSize;

	// Constructor
	Attribute(string n, Type ty) : t(ty), name(n) { }
	Attribute(string n, Type ty, int size) : t(ty), name(n), vcSize(size), hasSize(true) { }

	Attribute() : t(INTEGER), name("default") { }

	// Functions
	static bool compareAttribute(Attribute a,Attribute b) {
		return ( a.name < b.name ); 
	}

};

bool operator==( const Attribute& attribute1, const Attribute& attribute2 );

bool operator!=( const Attribute& attribute1, const Attribute& attribute2 );


#endif