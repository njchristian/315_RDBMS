#ifndef DATABASE_H_
#define DATABASE_H_

#include "Relation.h"
#include "Attribute.h"
#include "Type.h"
#include "ConditionList.h"
#include "Condition.h"
#include <vector>

class Database {

	//It might be useful to have a relation which we use to store results
	Relation result;

	// Data Members
	vector<Relation*> relations; //might need to be public

	// Private Functions
	Relation* findRelation( string relationName );

public:
	// Constructor
	Database( ) { }

	// Public Functions

	Attribute* accessAttribute( string name, string relationName );

	Relation accessRelation( string name );
	Relation* accessRelationPointer( string name );

	Entry accessTuple( );

	void addRelationToDatabase( string name, vector<Attribute> attributes, 
		vector<int> keys );
		
	void addRelationToDatabase( Relation r );

	void addTupleToRelation( vector<Entry> tuple, Relation* targetRelation );
	void addTupleToRelation( vector<Entry> tuple, Relation relationA ) { return addTupleToRelation( tuple, &relationA ); }
	void addTupleToRelation( vector<Entry> tuple, string relationName ) { return addTupleToRelation( tuple, findRelation( relationName ) ); }

	// do these need to return Relation* or void???
	Relation* insertIntoFromRelation( Relation* relationA, Relation* relationB );
	Relation* insertIntoFromRelation( Relation* relationA, Relation relationB ){ return insertIntoFromRelation( relationA, &relationB); }
	Relation* insertIntoFromRelation( string relationA, Relation* relationB ) { return insertIntoFromRelation( findRelation( relationA ), relationB ); }
	Relation* insertIntoFromRelation( Relation relationA, Relation relationB ) { return insertIntoFromRelation( &relationA, &relationB ); }

	void removeRelationFromDatabase( string relationName );

	
	Relation crossProduct( Relation* targetRelationA, Relation* targetRelationB );
	Relation crossProduct( Relation* targetRelationA, string relationB ){ return crossProduct(targetRelationA, findRelation(relationB)); }
	Relation crossProduct( string relationA, Relation* targetRelationB ){ return crossProduct(findRelation(relationA), targetRelationB); }
	Relation crossProduct( string relationA, string relationB ){ return crossProduct(findRelation(relationA) , findRelation(relationB)); }
	Relation crossProduct( Relation targetRelationA, Relation targetRelationB ){ return crossProduct( &targetRelationA, &targetRelationB ); }

	Relation deleteFromRelation( Relation* relationA, vector<Condition> conditions);
	Relation deleteFromRelation( string relationA, vector<Condition> conditions){ return deleteFromRelation(findRelation(relationA), conditions); }

	Relation differenceTwoRelation( Relation* targetRelationA, Relation* targetRelationB );
	Relation differenceTwoRelation( Relation targetRelationA, Relation targetRelationB ) { return differenceTwoRelation( &targetRelationA, &targetRelationB ); }
	Relation differenceTwoRelation( Relation* targetRelationA, string relationB ){ return differenceTwoRelation(targetRelationA, findRelation(relationB)); }
	Relation differenceTwoRelation( string relationA, Relation* targetRelationB ){ return differenceTwoRelation(findRelation(relationA), targetRelationB); }
	Relation differenceTwoRelation( string relationA, string relationB ){ return differenceTwoRelation(findRelation(relationA) , findRelation(relationB)); }

	int findAttribute( );

	int findCorrespondingRow( vector<Entry*> rowA, vector<int> indexA, Relation* b, vector<int> indexB );

	int findRelationinDatabase( );

	int findTuple( );

	vector<vector<string>> getResultMatrix();

	Relation naturalJoin( Relation* targetRelationA, Relation* targetRelationB);
	Relation naturalJoin( Relation* targetRelationA, string relationB ){ return naturalJoin(targetRelationA, findRelation(relationB)); }
	Relation naturalJoin( string relationA, Relation* targetRelationB ){ return naturalJoin(findRelation(relationA), targetRelationB); }
	Relation naturalJoin( string relationA, string relationB ){ return naturalJoin(findRelation(relationA) , findRelation(relationB)); }

	Relation projection( vector<string> attributeNames, Relation* targetRelation );
	Relation projection( vector<string> attributeNames, Relation targetRelation ) { return projection( attributeNames, &targetRelation ); }
	Relation projection( vector<string> attributeNames, string relationName ){ return projection(attributeNames, findRelation(relationName)); }

	void removeTupleFromRelation( vector<Entry> tuple, string relationName );

	Relation renameAttributes( vector<string> newNames, Relation* targetRelation );
	Relation renameAttributes( vector<string> newNames, Relation targetRelation ) { return renameAttributes( newNames, &targetRelation ); }
	Relation renameAttributes( vector<string> newNames, string relationName ){ return renameAttributes( newNames, findRelation(relationName)); }
	
	bool relationExists( string r );
	
	Relation selection( vector<Condition> conditions, Relation* targetRelation);
	Relation selection( vector<Condition> conditions, Relation targetRelation ) { return selection( conditions, &targetRelation ); }
	Relation selection( vector<Condition> conditions, string targetRelationName ){ return selection( conditions, findRelation( targetRelationName)); }

	Relation unionTwoRelations( Relation* targetRelationA, Relation* targetRelationB );
	Relation unionTwoRelations( Relation targetRelationA, Relation targetRelationB ) { return unionTwoRelations( &targetRelationA, &targetRelationB ); }
	Relation unionTwoRelations( Relation* targetRelationA, string relationB ){ return unionTwoRelations(targetRelationA, findRelation(relationB)); }
	Relation unionTwoRelations( string relationA, Relation* targetRelationB ){ return unionTwoRelations(findRelation(relationA), targetRelationB); }
	Relation unionTwoRelations( string relationA, string relationB ){ return unionTwoRelations(findRelation(relationA) , findRelation(relationB)); }

	Relation* update(string relationName, vector<string> attributeName, vector<Entry> newVal, vector<Condition> conditions);

};

#endif