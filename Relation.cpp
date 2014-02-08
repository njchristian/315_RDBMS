#include "Relation.h"


void Relation::clear(){

	attributes.clear();
	table.clear();
	keys.clear();

}

vector<string> Relation::getAttributes(){

	vector<string> result;

	for(int i = 0; i < attributes.size(); i++){
		result.push_back(attributes.at(i).name);
	}

	return result;
}