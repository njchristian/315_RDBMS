#include "Relation.h"


void Relation::clear( ){

	attributes.clear( );
	table.clear( );
	keys.clear( );

}


/*
vector<string> Relation::getAttributes(){

	vector<string> result;

	for(int i = 0; i < attributes.size(); i++){
		result.push_back(attributes.at(i).name);
	}

	return result;
}
*/

bool Relation::hasTuple( vector<Entry*> tuple ) {
	for ( unsigned i = 0; i < table.size( ); ++i ) {
		if ( table[ i ] == tuple ) {
			return true;
		}
	}

	return false;
}