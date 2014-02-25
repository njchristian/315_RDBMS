#include "ConditionList.h"

// Constructor
//The constructor does the majority of the work here. It sets up the Conditions
//with the variable indexes and prepares the list for quick evaluations. 
ConditionList::ConditionList( vector<Condition> givenConditions, Relation* r ) :
targetRelation( r ) {

	highestPriority = 0;

	//initialize linked list - also set highest priority
	for ( unsigned int i = 0; i < givenConditions.size( ); i++ ) {

		if ( givenConditions.at( i ).getPriority( ) > highestPriority ) {
			highestPriority = givenConditions.at( i ).getPriority( );
		}

		conditions.push_back( givenConditions.at( i ) );

	}

	//replace any variable names with the proper index
	for ( list<Condition>::iterator i = conditions.begin( );
		i != conditions.end( ); i++ ) {

		if ( i->firstIsVar( ) ) {
			i->setVar1Index( findVarNameIndex( targetRelation,
				i->firstVarName( ) ) );
		}

		if ( i->secondIsVar( ) ) {
			i->setVar2Index( findVarNameIndex( targetRelation,
				i->secondVarName( ) ) );
		}
	}

}


// Evaluate the tuple to see if it meets the conditions.
bool ConditionList::evalOnTuple( int tupleIndex ) {

	list<Condition> localConditions = conditions;
	int localHP = highestPriority;

	//Turn the condition list into a list of true/false literals by substituting
	//in the attribute values for the tuple, and then evaluating the conditions
	for ( list<Condition>::iterator i = localConditions.begin( );
		i != localConditions.end( ); i++ ) {

		if ( i->firstIsVar( ) ) {
			i->setOperand1Entry( *targetRelation->getEntry( tupleIndex,
				i->getVar1Index( ) ) );
		}

		if ( i->secondIsVar( ) ) {
			i->setOperand2Entry( *targetRelation->getEntry( tupleIndex,
				i->getVar2Index( ) ) );
		}

		i->eval( );

	}

	//An often used special case. If we just had one condition go ahead and return
	if ( localConditions.size( ) == 1 ) {
		return localConditions.front( ).getLiteral( );
	}

	//After consolidating two literals, we reduce their priority by one. Thus
	//we loop until all priorities are 0 which means we have only one value left
	while ( localHP > 0 ) {


		for ( list<Condition>::iterator i = localConditions.begin( );
			i != localConditions.end( ); i++ ) {

			if ( i->getPriority( ) == highestPriority ) {

				i++;
				list<Condition>::iterator next = i;
				i--;


				//update current value
				switch ( i->getConnector( ) ) {
				case ( AND ) :
					i->setLiteral( i->getLiteral( ) && next->getLiteral( ) );
					i->decPriority( );
					i->setConnector( next->getConnector( ) );
					localConditions.erase( next );
					break;
				case ( OR ) :
					i->setLiteral( i->getLiteral( ) || next->getLiteral( ) );
					i->decPriority( );
					i->setConnector( next->getConnector( ) );
					localConditions.erase( next );
					break;
				case ( NONE ) :
					break;
				}

			}

		}

		localHP--;

	}

	//and now the one value left is the literal respresentation of the complex condition
	return localConditions.front( ).getLiteral( );

}


// Returns the index of the given variable name in the specified relation.
int ConditionList::findVarNameIndex( Relation* r, string target ) {

	for ( int i = 0; i < r->attributeSize( ); i++ ) {
		if ( target == r->getAttributeNameAt( i ) ) {
			return i;
		}

	}

	cout << "ERROR in findVarNameIndex in ConditionList.cpp";
	// error value so compiler won't complain
	return -1;
}
