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
	
	Connector c;
	
	// Constructor
	Condition(Operation givenOperation, Entry givenOperand) : o(givenOperation), operand(givenOperand){
		isLiteral = false;
	}
	
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
	
	void setLiteral(bool l){ lit = l;}
	void setConnector(Connector c){ connector = c;}
	
	Connector getConnector(){ return connector; }
	
	bool eval(){
	
	//if integer argument do one switch
	
	
	if(operand1.getEntryType() == INTEGER) {
	
	int a = operand1.getEntryI();
	int b = operand2.getEntryI();
	
		switch (o){
		
		case EQUALS:
			//LIKEWISE FOR THE REST OF THE FUNCTION
			lit = (a==b);
			break;
		case GR:

			break;
		case GREQ:

			break;
		case LE:

			break;
		case LEEQ:

			break;
		case NEQ:

			break;					
		default:
			cout << "Something went wrong...\n";
			break; // might not need this break
		}
	
	}
	//else do other switch for strings. We just need equals and not equals right!?
	else {
		switch (o) {
			case EQUALS:

				break;
			case NEQ:
			
				break;	
			default:
				cout << "Invalid operation for strings.\n";
				break;	
		}
	}
	
	
	
	isLit = true;

};



