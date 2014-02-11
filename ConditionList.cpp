#include "ConditionList.h"

// Constructor
ConditionList::ConditionList( vector<Condition> givenConditions, Relation* r ) :
	targetRelation( r ) {

	highestPriority = 0;

	//initialize linked list - also set highest priority
	for ( unsigned int i = 0; i < givenConditions.size( ); i++ ){

		if ( givenConditions.at( i ).getPriority( ) > highestPriority ){
			highestPriority = givenConditions.at( i ).getPriority( );
		}

		conditions.push_back( givenConditions.at( i ) );

	}

	//replace any variable names with the proper index
	for ( list<Condition>::iterator i = conditions.begin( );
		i != conditions.end( ); i++ ){

		if ( i->firstIsVar( ) ){
			i->setVar1Index( findVarNameIndex( targetRelation,
				i->firstVarName( ) ) );
		}

		if ( i->secondIsVar( ) ){
			i->setVar2Index( findVarNameIndex( targetRelation,
				i->secondVarName( ) ) );
		}
	}

}


// Evaluate the tuple to see if it meets the conditions.
bool ConditionList::evalOnTuple( int tupleIndex ) {

	list<Condition> localConditions = conditions;
	int localHP = highestPriority;

	// Loop through the conditions and evaluate
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

	while ( localHP > 0 ) {

		for ( list<Condition>::iterator i = localConditions.begin( );
			i != localConditions.end( ); i++ ){

			if ( i->getPriority( ) == highestPriority ){

				
				// Get i.next
				i++;
				list<Condition>::iterator next = i;
				i--;


				// Update current value
				switch ( i->getConnector( ) ){
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

	return localConditions.front( ).getLiteral( );

}


// Returns the index of the given variable name in the specified relation.
int ConditionList::findVarNameIndex( Relation* r, string target ) {

	// find the index of the variable name
	for ( int i = 0; i < r->attributeSize( ); i++ ){
		if ( target == r->getAttributeNameAt( i ) ){
			return i;
		}

	}
	// error value so compiler won't complain
	return -1;
}