#include "Database.h"
#include "Attribute.h"
#include "Entry.h"
#include "Condition.h"
#include "Type.h"
#include <vector>

int main(){

	Database d;

	vector<Attribute> testAtts;
	vector<int> keys;
	vector<vector<Entry>> entries;

	testAtts.push_back(Attribute("Name", VARCHAR));
	testAtts.push_back(Attribute("Owner", VARCHAR));
	testAtts.push_back(Attribute("Age", INTEGER));

	
	keys.push_back(0);
	keys.push_back(2);

	entries.push_back(vector<Entry>());
	entries.push_back(vector<Entry>());
	entries.push_back(vector<Entry>());

	entries.at(0).push_back(Entry("Abby"));
	entries.at(0).push_back(Entry("Amy"));
	entries.at(0).push_back(Entry(3));

	entries.at(1).push_back(Entry("Zipper"));
	entries.at(1).push_back(Entry("Melodie"));
	entries.at(1).push_back(Entry(14));

	entries.at(2).push_back(Entry("Bailey"));
	entries.at(2).push_back(Entry("Davin"));
	entries.at(2).push_back(Entry(6));
	
	d.addRelationToDatabase("Dogs", testAtts, keys);

	d.addTupleToRelation(entries.at(0), "Dogs");
	d.addTupleToRelation(entries.at(1), "Dogs");
	d.addTupleToRelation(entries.at(2), "Dogs");

	vector<Condition> c;

	/***************
	Test select(age > 4 && (owner == "Melodie" || owner == "Davin") )
	***************/
	//*Sidenote: This is how the parser will add these. This is a pretty simple and intuitive
	//implementation in that respect
	c.push_back(Condition("Age", GR, 4, AND, 1));
	c.push_back(Condition("Owner", EQUALS, Entry("Melodie"), OR, 2));
	c.push_back(Condition("Owner", EQUALS, Entry("Davin"), NONE, 2));

	Relation r = d.selection(c, "Dogs");


	return 1;
}