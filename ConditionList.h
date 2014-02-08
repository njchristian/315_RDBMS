#ifndef CONDITIONLIST_H_
#define CONDITIONLIST_H_

#include "Condition.h"
#include "Connector.h"
#include "Relation.h"
#include <list>

using namespace std;

class ConditionList{

	list<Condition> conditions;
	Relation* targetRelation;
	
	int highestPriority;
	
	int findVarNameIndex(Relation* r, string target);
	
public:

	ConditionList(vector<Condition> givenConditions, Relation* r);

	bool evalOnTuple( int index );


};

#endif