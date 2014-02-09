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

	Entry accessAttribute( );

	Relation* accessRelation( string name );

	Entry accessTuple( );

	void addRelationToDatabase( string name, vector<Attribute> attributes, 
		vector<int> keys );

	void addTupleToRelation( vector<Entry> tuple, string relationName );

	Relation crossProduct( Relation* targetRelationA, Relation* targetRelationB );
	Relation crossProduct( Relation* targetRelationA, string relationB ){ crossProduct(targetRelationA, findRelation(relationB)); }
	Relation crossProduct( string relationA, Relation* targetRelationB ){ crossProduct(findRelation(relationA), targetRelationB); }
	Relation crossProduct( string relationA, string relationB ){ crossProduct(findRelation(relationA) , findRelation(relationB)); }

	Relation differenceTwoRelation( Relation* targetRelationA, Relation* targetRelationB );
	Relation differenceTwoRelation( Relation* targetRelationA, string relationB ){ differenceTwoRelation(targetRelationA, findRelation(relationB)); }
	Relation differenceTwoRelation( string relationA, Relation* targetRelationB ){ differenceTwoRelation(findRelation(relationA), targetRelationB); }
	Relation differenceTwoRelation( string relationA, string relationB ){ differenceTwoRelation(findRelation(relationA) , findRelation(relationB)); }

	int findAttribute( );

	int findRelationinDatabase( );

	int findTuple( );

	Relation naturalJoin( Relation* targetRelationA, Relation* targetRelationB);
	Relation naturalJoin( Relation* targetRelationA, string relationB ){ naturalJoin(targetRelationA, findRelation(relationB)); }
	Relation naturalJoin( string relationA, Relation* targetRelationB ){ naturalJoin(findRelation(relationA), targetRelationB); }
	Relation naturalJoin( string relationA, string relationB ){ naturalJoin(findRelation(relationA) , findRelation(relationB)); }

	Relation projection( vector<string> attributeNames, Relation* targetRelation );
	Relation projection( vector<string> attributeNames, string relationName ){ projection(attributeNames, findRelation(relationName)); }

	void removeTupleFromRelation( );

	Relation renameAttributes( vector<string> newNames, Relation* targetRelation );
	Relation renameAttributes( vector<string> newNames, string relationName ){ renameAttributes( newNames, findRelation(relationName)); }
	
	Relation selection( vector<Condition>, Relation* targetRelation);
	Relation selection( vector<Condition> conditions, string targetRelationName ){ selection( conditions, findRelation( targetRelationName)); }

	Relation unionTwoRelations( Relation* targetRelationA, Relation* targetRelationB );
	Relation unionTwoRelations( Relation* targetRelationA, string relationB ){ unionTwoRelations(targetRelationA, findRelation(relationB)); }
	Relation unionTwoRelations( string relationA, Relation* targetRelationB ){ unionTwoRelations(findRelation(relationA), targetRelationB); }
	Relation unionTwoRelations( string relationA, string relationB ){ unionTwoRelations(findRelation(relationA) , findRelation(relationB)); }

};

#endif