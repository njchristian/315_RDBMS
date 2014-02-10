#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Database/Database.h"
#include "../Database/Relation.h"
#include "../Database/Attribute.h"
#include "../Database/Entry.h"
#include "../Database/Condition.h"
#include "../Database/Type.h"
#include <vector>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			
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

			Relation* dogs = d.accessRelation("Dogs");

			//testing projection
			//to really test projection we need to overload the == operator for relations
			Assert::AreEqual( d.projection( dogs->getAttributeNames(), dogs->getName() ).getName(), dogs->getName() ); //testing projection
			
			vector<Attribute> dogAttributes = dogs->getAttributes();
			string name = "Name";

			Assert::AreEqual( d.accessAttribute( dogAttributes[0].name, "Dogs" )->name , name); //testing insert attributes

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

			//test set union
			Assert::AreEqual( ( d.unionTwoRelations( "More Dogs" , "Dogs" ) ).getNumTuples(),
				( d.unionTwoRelations( "Dogs" , "More Dogs" ) ).getNumTuples() );

			//test set difference

			//test cross product
			Assert::AreEqual( ( d.crossProduct( "More Dogs" , "Dogs" ) ).getNumTuples(),
				( d.crossProduct( "Dogs" , "More Dogs" ) ).getNumTuples() );

			//test natural join


			//testing renaming
			vector<string> newAttributeName;
			newAttributeName.push_back("Dog Name");
			newAttributeName.push_back("Owner Name");
			newAttributeName.push_back("Dog age");

			
			Assert::AreEqual( d.renameAttributes( newAttributeName, dogs->getName() ).getAttributeNames()[0], newAttributeName[0]  );
			Assert::AreEqual( d.renameAttributes( newAttributeName, dogs->getName() ).getAttributeNames()[1], newAttributeName[1]  );
			Assert::AreEqual( d.renameAttributes( newAttributeName, dogs->getName() ).getAttributeNames()[2], newAttributeName[2]  );

			Assert::AreEqual(1,1); //testing test
		}

	};
}