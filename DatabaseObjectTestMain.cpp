#include "Database.h"
#include "Relation.h"
#include "Attribute.h"
#include "Entry.h"
#include "Condition.h"
#include "Type.h"
#include <vector>
#include <iostream>

using namespace std;

int main(){

	Database d;

	//In the final project, this is stored in the database cell. This is for the relations the
	//user create via assignment (the <- operator).
	vector<Relation*> localRelations;

	vector<Attribute> testAtts;
	vector<int> keys;
	vector<vector<Entry>> entries;
	vector<vector<Entry>> e2;

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

	localRelations.push_back( new Relation( d.selection(c, "Dogs") ));
	localRelations.at(0)->setName("Selection of Dogs");

	cout<<*localRelations.at(0)<<"\n\n";

	e2.push_back(vector<Entry>());
	e2.push_back(vector<Entry>());
	e2.push_back(vector<Entry>());

	e2.at(0).push_back(Entry("Tyler"));
	e2.at(0).push_back(Entry("Garren"));
	e2.at(0).push_back(Entry(5));

	e2.at(1).push_back(Entry("Abby"));
	e2.at(1).push_back(Entry("Amy"));
	e2.at(1).push_back(Entry(3));

	e2.at(2).push_back(Entry("Dusty"));
	e2.at(2).push_back(Entry("Rodger"));
	e2.at(2).push_back(Entry(11));

	d.addRelationToDatabase("More Dogs", testAtts, keys);

	d.addTupleToRelation(e2.at(0), "More Dogs");
	d.addTupleToRelation(e2.at(1), "More Dogs");
	d.addTupleToRelation(e2.at(2), "More Dogs");

	localRelations.push_back(new Relation(d.unionTwoRelations("Dogs", "More Dogs") ));
	localRelations.at(1)->setName("Lots of Dogs");

	cout<<*localRelations.at(1)<<'\n';
	
	localRelations.push_back(new Relation(d.differenceTwoRelation("Dogs", "More Dogs") ));
	localRelations.at(2)->setName("Difference");

	cout<<*localRelations.at(2)<<'\n';

	return 1;
}