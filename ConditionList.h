#ifndef CONDITIONLIST_H_
#define CONDITIONLIST_H_

#include "Condition.h"
#include "Connector.h"
#include "Relation.h"
#include <list>

using namespace std;

/********************************
*See Condition.h first*

A complex condition in our program is stored 
as a list of individual condition objects. As we
have already seen, a condition contains a connector
and a priority. The connector is the AND or OR that
connects conditions, and the priority is a numerical
representation of the order of operations. By this,
we primarily mean nested parentheses. Our method of
evaluation is simply to evaluate all conditions at
the highest priority first (surrounded by the most
parentheses) and then work our way down. 
********************************/

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