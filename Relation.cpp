#include "Relation.h"


Relation::Relation( Relation* r ){

	relationName = r->getName( );
	attributes = r->getAttributes( );

	for ( int i = 0; i < r->getNumTuples( ); i++ ){

		table.push_back( vector<Entry*>( ) );

		for ( int j = 0; j < r->attributeSize( ); j++ ){

			table.at( i ).push_back( new Entry( *r->getEntry( i, j ) ) );

		}

	}

}

void Relation::addRow( vector<Entry*> rowToAdd ) {
	table.push_back( rowToAdd );
}

void Relation::clear( ){

	attributes.clear( );
	table.clear( );
	keys.clear( );

}

vector<string> Relation::getAttributeNames(){

	vector<string> result;

	for (int i = 0; i < attributes.size(); i++){
		result.push_back(attributes.at(i).name);
	}

	return result;
}

bool Relation::hasTuple( vector<Entry*> tuple ) {
	for ( unsigned i = 0; i < table.size( ); ++i ) {
		if ( table[ i ] == tuple ) {
			return true;
		}
	}

	return false;
}

Relation& Relation::operator=(Relation& b){

	relationName = b.getName();
	attributes = b.getAttributes();
	table = b.getAllEntries();

	keys = b.getKeys();

	return *this;

}

ostream& operator<<(ostream& os, Relation& a){

	os<<"Name: "<<a.getName()<<"\n\n";

	for(int i = 0; i < a.getNumTuples(); i++){

		stringstream ss;
		string tempS;
		for(int j = 0; j < a.attributeSize(); j++){

			Entry* t = a.getEntry(i, j);
			if(t->isInt()){
				ss<<t->getEntryI();
			}else{
				ss<<t->getEntryVC();
			}

			ss>>tempS;
			os<<tempS<<' ';

			ss.clear();
		}
		os<<'\n';
	}

	return os;
}