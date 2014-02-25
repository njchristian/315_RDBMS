#include "Entry.h"

bool operator==( Entry& entry1, Entry& entry2 ) {
	if ( entry1.getEntryType( ) != entry2.getEntryType( ) ) {
		return false;
	}
	if ( entry1.getEntryType( ) == INTEGER ) {
		return entry1.getEntryI( ) == entry2.getEntryI( );
	}
	else {
		return entry1.getEntryVC( ) == entry2.getEntryVC( );
	}
}

bool operator!=( Entry& entry1, Entry& entry2 ) {
	return !( entry1 == entry2 );
}