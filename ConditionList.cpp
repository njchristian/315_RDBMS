#include "ConditionList.h"

	ConditionList::ConditionList(vector<Condition> givenConditions, Relation* r) : targetRelation(r) {
	
		highestPriority = 0;
	
		//initialize linked list - also set highest priority
		for(int i = 0; i < givenConditions.size(); i++){
		
			if(givenConditions.at(i).getPriority() > highestPriority){
				highestPriority = givenConditions.at(i).getPriority();
			}
			
			conditions.push_back(givenConditions.at(i));
		
		}
		
		//replace any variable names with the proper index
		for(list<Condition>::iterator i = conditions.begin(); i != conditions.end(); i++){
			if(i->firstIsVar()){
				i->setVar1Index( findVarNameIndex( targetRelation, i->firstVarName() ) );
			}
		
			if(i->secondIsVar()){
				i->setVar2Index( findVarNameIndex( targetRelation, i->secondVarName() ) );
			}
		}
	
	}


	bool ConditionList::evalOnTuple(int tupleIndex){
	
		list<Condition> localConditions = conditions;
		int localHP = highestPriority;
	
		for(list<Condition>::iterator i = localConditions.begin(); i != localConditions.end(); i++){
		
			

			if(i->firstIsVar()){
				i->setOperand1Entry(*targetRelation->getEntry(tupleIndex, i->getVar1Index() ));
			}
			
			if(i->secondIsVar()){
				i->setOperand2Entry(*targetRelation->getEntry(tupleIndex, i->getVar2Index() ));
			}
			
			i->eval();
			
		}
	
		while(localHP > 0){
		
			for(list<Condition>::iterator i = localConditions.begin(); i != localConditions.end(); i++){
				
				if(i->getPriority() == highestPriority){
					
					/*************
					I don't know how else to get i.next..
					*************/
					i++;
					list<Condition>::iterator next = i;
					i--;
					
					
					//update current value
					switch (i->getConnector()){
					case (AND):
						i->setLiteral( i->getLiteral() && next->getLiteral());
						i->decPriority();
						i->setConnector(next->getConnector());
						conditions.erase(next);
						break;
					case (OR):
						i->setLiteral( i->getLiteral() || next->getLiteral());
						i->decPriority();
						i->setConnector(next->getConnector());
						conditions.erase(next);
						break;
					case (NONE):
						break;
					}
					
				}
				
			}

			localHP--;
		
		}
		
		return localConditions.front().getLiteral();
	
	}

	int ConditionList::findVarNameIndex(Relation* r, string target){
	
		for(int i = 0; i < r->attributeSize(); i++){
			if(target == r->getAttributeNameAt(i)){
				return i;
			}
		
		}
	
	}