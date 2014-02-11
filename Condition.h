#ifndef CONDITION_H_
#define CONDITION_H_

#include "Entry.h"
#include "Connector.h"

enum Operation{EQUALS, GR, GREQ, LE, LEEQ, NEQ};

class Condition{

	bool isLiteral;
	bool lit;

	//Operand1
	bool isVar1;
	int varIndex1;
	string varName1;
	Entry operand1;
	
	//operand2
	bool isVar2;
	int varIndex2;
	string varName2;
	Entry operand2;
	

	// Data Members
	Operation o;
	
	Connector connector;

	int priority;

public:

	// Constructors

	//two literals (Rarely Used..)
	Condition(Entry o1, Operation givenOp, Entry o2, Connector givenC, int p);
	//var, lit
	Condition(string var1, Operation givenOp, Entry o2, Connector givenC, int p);
	//lit, var
	Condition(Entry o1, Operation givenOp, string var2, Connector givenC, int p);
	//var, var
	Condition(string var1, Operation givenOp, string var2, Connector givenC, int p);
	
	// Functions

	bool firstIsVar(){return isVar1;}
	bool secondIsVar(){ return isVar2;}
	
	string firstVarName(){ return varName1;}
	string secondVarName() { return varName2;}

	void setVar1Index(int i){
		varIndex1 = i;
	}
	
	void setVar2Index(int i){
		varIndex2 = i;
	}
	
	int getVar1Index(){ return varIndex1; }
	int getVar2Index(){ return varIndex2; }
	
	void setOperand1Entry(Entry e){
		operand1 = e;
	}
	
	void setOperand2Entry(Entry e){
		operand2 = e;
	}
	
	int getPriority(){ return priority; }
	void decPriority(){ priority-=1; }
	
	void setLiteral(bool l){ lit = l; }
	void setConnector(Connector c){ connector = c;}
	
	bool getLiteral(){ return lit; }
	Connector getConnector(){ return connector; }
	
	void eval();
};

#endif