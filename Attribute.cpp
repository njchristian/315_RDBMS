#include "Attribute.h"


// Overloaded == operator
bool operator==( const Attribute& attribute1, const Attribute& attribute2 ) {
	if ( attribute1.t == attribute2.t && attribute1.name == attribute2.name ) {
		return true;
	}
	return false;
}


// Overloaded != operator
bool operator!=( const Attribute& attribute1, const Attribute& attribute2 ) {
	return !( attribute1 == attribute2 );
}