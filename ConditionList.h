#ifndef CONDITIONLIST_H_
#define CONDITIONLIST_H_

#include "Condition.h"
#include "Connector.h"
#include "Relation.h"
#include <list>

using namespace std;

class ConditionList {

	// Data members
	list<Condition> conditions;

	Relation* targetRelation;
	
	int highestPriority;
	
	int findVarNameIndex(Relation* r, string target);
	
public:

	// Constructor
	ConditionList(vector<Condition> givenConditions, Relation* r);

	// Functions
	bool evalOnTuple( int index );


};

#endif