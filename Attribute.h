#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include "Type.h"
#include <string>

using namespace std;

struct Attribute{

	// Data members
	Type t;
	string name;

	// Constructor
	Attribute(string n, Type ty) : t(ty), name(n) { }

	// Functions
	static bool compareAttribute(Attribute a,Attribute b) {
		return ( a.name < b.name ); 
	}

};

bool operator==( const Attribute& attribute1, const Attribute& attribute2 );

bool operator!=( const Attribute& attribute1, const Attribute& attribute2 );


#endif