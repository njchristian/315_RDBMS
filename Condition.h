

enum Operation{EQUALS, GR, GREQ, LE, LEEQ, NEQ}


class Condition{

	// Data Members
	Operation o;
	
	Entry operand;
	
	// Constructor
	Condition(Operation givenOperation, Entry givenOperand) : o(givenOperation), operand(givenOperand){ }
	
	// Functions
	bool eval(Entry firstOperand){
	
	//if integer argument do one switch
	
	
	if(firstOperand.getEntryType() == INTEGER) {
	
		switch (o){
		
		case EQUALS:

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
	
	
	
	
	//....Finish later

}