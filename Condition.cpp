#include "Condition.h"


//two literals (Rarely Used..)
Condition::Condition(Entry o1, Operation givenOp, Entry o2, 
	Connector givenC, int p) : priority(p) {

	isVar1 = false;
	isVar2 = false;

	operand1 = o1;
	operand2 = o2;

	o = givenOp;
	connector = givenC;

	isLiteral = false;

}
//var, lit
Condition::Condition(string var1, Operation givenOp, Entry o2, 
	Connector givenC, int p) : priority(p){

	isVar1 = true;
	isVar2 = false;

	varName1 = var1;
	operand2 = o2;

	o = givenOp;
	connector = givenC;

	isLiteral = false;

}
//lit, var
Condition::Condition(Entry o1, Operation givenOp, string var2, 
	Connector givenC, int p) : priority(p){

	isVar1 = false;
	isVar2 = true;

	operand1 = o1;
	varName2 = var2;

	o = givenOp;
	connector = givenC;

	isLiteral = false;

}
//var, var
Condition::Condition( string var1, Operation givenOp, string var2, 
	Connector givenC, int p ) : priority( p ) {

	isVar1 = true;
	isVar2 = true;

	varName1 = var1;
	varName2 = var2;

	o = givenOp;
	connector = givenC;

	isLiteral = false;


}



//sets the condition to a literal value;
void Condition::eval( ) {

	//if integer argument do one switch


	if ( operand1.getEntryType( ) == INTEGER ) {

		int a = operand1.getEntryI( );
		int b = operand2.getEntryI( );

		switch ( o ){

		case EQUALS:
			//LIKEWISE FOR THE REST OF THE FUNCTION
			lit = ( a == b );
			break;
		case GR:
			lit = ( a > b );
			break;
		case GREQ:
			lit = ( a >= b );
			break;
		case LE:
			lit = ( a < b );
			break;
		case LEEQ:
			lit = ( a <= b );
			break;
		case NEQ:
			lit = ( a != b );
			break;
		default:
			cout << "Something went wrong...\n";
			break; // might not need this break
		}

	}
	//else do other switch for strings. We just need equals and not equals right!?
	else {
		string a = operand1.getEntryVC( );
		string b = operand2.getEntryVC( );

		switch ( o ) {
		case EQUALS:
			lit = ( a == b );
			break;
		case NEQ:
			lit = ( a != b );
			break;
		default:
			cout << "Invalid operation for strings.\n";
			break;
		}
	}



	isLiteral = true;


}
