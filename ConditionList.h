#include "Condition.h"
#include "Connector.h"
#include "Relation.h"
#include <linkedlist>

class ConditionList{

	LinkedList<Condition> conditions;
	Relation& targetRelation;
	
	int highestPriority;
	
	int findVarNameIndex(Relation& r, string target){
	
		for(int i = 0; i < r.attributeSize(); i++){
			if(target == r.getAttributeNameAt(i)){
				return i;
			}
		
		}
	
	}
	
public:

	ConditionList(vector<Condition> givenConditions, Relation& r){
	
		highestPriority = 0;
	
		//initialize linked list - also set highest priority
		for(int i = 0; i < givenConditions.size(); i++){
		
			if(givenConditions.at(i).getPriority() > highestPriority){
				highestPriority = givenConditions.at(i).getPriority();
			}
			
			conditions.push_back(givenConditions.at(i));
		
		}
		
		//replace any variable names with the proper index
		for(Condition::Iterator i = conditions.begin(); i != conditions.end(); i++){
			if(i->firstIsVar()){
				i->setVar1Index( findVarNameIndex( i->firstVarName() ) );
			}
		
			if(i->secondIsVar()){
				i->setVar2Index( findVarNameIndex( i->secondVarName() ) );
			}
		}
	
	}

	bool evalOnTuple(int tupleIndex){
	
		LinkedList<Condition> localConditions = conditions;
	
		for(Condition::Iterator i = localConditions.begin(); i != localConditions.end(); i++){
		
			if(i->firstIsVar(){
				i->setOperand1Entry(r.getEntry(tupleIndex, i->getVar1Index));
			}
			
			if(i->secondIsVar(){
				i->setOperand2Entry(r.getEntry(tupleIndex, i->getVar2Index));
			}
			
			i->eval();
			
		}
	
		while(highestPriority > 0){
		
			for(Condition::Iterator i = localConditions.begin(); i != localConditions.end(); i++){
				
				if(i->getPriority == highestPriority){
					Condition::Iterator next = i.next();
					
					
					//update current value
					switch (i->getConnector()){
					case (AND):
						i->setLiteral( i->getLiteral() && next->getLiteral());
						i->setConnector(next->getConnector());
						conditions.remove(next);
						break;
					case (OR):
						i->setLiteral( i->getLiteral() || next->getLiteral());
						i->setConnector(next->getConnector());
						conditions.remove(next);
						break;
					case (NONE):
						break;
					}
					
				}
				
			}
		
		}
		
		return conditions.front().getLiteral();
	
	}


}