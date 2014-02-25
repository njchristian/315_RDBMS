#ifndef ENTRY_H_
#define ENTRY_H_

#include "Type.h"
#include <iostream>
#include <string>

using namespace std;

class Entry {

	// Data Members
	Type t;
	int intEntry;
	string vcEntry;
	int vcLength;

	void storeStr( string s ) {

		if ( s.size( ) <= vcLength ) {
			vcEntry = s;
			return;
		}

		string result = "";

		for ( int i = 0; i < vcLength; ++i ) {

			result.push_back( s.at( i ) );

		}

		vcEntry = result;

	}

public:

	// Constructors
	Entry( ) {}

	Entry( int givenInt ) : intEntry( givenInt ) {
		t = INTEGER;
	}

	Entry( string givenVC, int len ) : vcLength( len ) {
		storeStr( givenVC );
		t = VARCHAR;
	}

	void setInt( int i ) {
		intEntry = i;
		t = INTEGER;
	}

	void setVC( string str ) {
		storeStr( str );
		t = VARCHAR;
	}

	void setL( int length ) {
		vcLength = length;
	}

	// Public Functions
	bool isInt( ) {
		return t == INTEGER;
	}

	int getEntryI( ) {
		return intEntry;
	}

	Type getEntryType( ) {
		return t;
	}

	string getEntryVC( ) {
		return vcEntry;
	}

	int getVCLength( ) {
		return vcLength;
	}

};


bool operator==( Entry& entry1, Entry& entry2 );


bool operator!=( Entry& entry1, Entry& entry2 );


#endif