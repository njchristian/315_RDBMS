#include "stdafx.h"
#include "CppUnitTest.h"
#include "Database.h"
#include "Relation.h"
#include "Attribute.h"
#include "Entry.h"
#include "Condition.h"
#include "Type.h"
#include "Parser.h"
#include "DBCell.h"
#include "SportsLeague.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


//PLEASE RUN ON VS 2012

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		SportsLeague league;
		Database d;
		vector<vector<string>> r;
		
		vector<Relation*> localRelations;

		vector<Attribute> testAtts;
		vector<int> keys;
		vector<vector<Entry>> entries;
		vector<vector<Entry>> e2;
		

		TEST_METHOD_INITIALIZE(init234)
		{
			testAtts.push_back(Attribute("Name", VARCHAR, 10));
			testAtts.push_back(Attribute("Owner", VARCHAR, 10));
			testAtts.push_back(Attribute("Age", INTEGER));

	
			keys.push_back(0);
			keys.push_back(2);

			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());

			entries.at(0).push_back(Entry("Abby", 10));
			entries.at(0).push_back(Entry("Amy", 10));
			entries.at(0).push_back(Entry(1));


			entries.at(1).push_back(Entry("Zipper", 10));
			entries.at(1).push_back(Entry("Melodie", 10));
			entries.at(1).push_back(Entry(14));

			entries.at(2).push_back(Entry("Bailey", 10));
			entries.at(2).push_back(Entry("Davin", 10));
			entries.at(2).push_back(Entry(6));
	
			d.addRelationToDatabase("Dogs", testAtts, keys);

			d.addTupleToRelation(entries.at(0), "Dogs");
			d.addTupleToRelation(entries.at(1), "Dogs");
			d.addTupleToRelation(entries.at(2), "Dogs");

			//relation More_Dogs
			e2.push_back(vector<Entry>());
			e2.push_back(vector<Entry>());
			e2.push_back(vector<Entry>());

			e2.at(0).push_back(Entry("Tyler", 10));
			e2.at(0).push_back(Entry("Garren", 10));
			e2.at(0).push_back(Entry(5));

			e2.at(1).push_back(Entry("Abby", 10));
			e2.at(1).push_back(Entry("Amy", 10));
			e2.at(1).push_back(Entry(1));

			e2.at(2).push_back(Entry("Dusty", 10));
			e2.at(2).push_back(Entry("Rodger", 10));
			e2.at(2).push_back(Entry(11));

			d.addRelationToDatabase("More_Dogs", testAtts, keys);

			d.addTupleToRelation(e2.at(0), "More_Dogs");
			d.addTupleToRelation(e2.at(1), "More_Dogs");
			d.addTupleToRelation(e2.at(2), "More_Dogs");

			 Relation rel = d.naturalJoin( "More_Dogs", "Dogs" );
		}
		
		TEST_METHOD(create)
		{
		
			testAtts.push_back(Attribute("Name", VARCHAR, 10));
			testAtts.push_back(Attribute("Owner", VARCHAR, 10));
			testAtts.push_back(Attribute("Age", INTEGER));

	
			keys.push_back(0);
			keys.push_back(2);

			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());

			entries.at(0).push_back(Entry("Abby", 10));
			entries.at(0).push_back(Entry("Amy", 10));
			entries.at(0).push_back(Entry(3));


			entries.at(1).push_back(Entry("Zipper", 10));
			entries.at(1).push_back(Entry("Melodie", 10));
			entries.at(1).push_back(Entry(14));

			entries.at(2).push_back(Entry("Bailey", 10));
			entries.at(2).push_back(Entry("Davin", 10));
			entries.at(2).push_back(Entry(6));
	
			d.addRelationToDatabase("Dogs", testAtts, keys);

			d.addTupleToRelation(entries.at(0), "Dogs");
			d.addTupleToRelation(entries.at(1), "Dogs");
			d.addTupleToRelation(entries.at(2), "Dogs");
			
			

			//In the final project, this is stored in the database cell. This is for the relations the
			//user create via assignment (the <- operator).
			Relation dogs = d.accessRelation("Dogs");
			//testing projection
			//to really test projection we need to overload the == operator for relations
			Assert::AreEqual( d.projection( dogs.getAttributeNames(), dogs.getName() ).getAttributeAt(0).name, dogs.getAttributeAt(0).name ); //testing projection
		}

		TEST_METHOD(dropTable)
		{
			d.removeRelationFromDatabase( "Dogs" );

			string emptyString = "";

			Assert::AreEqual( d.accessRelation( "Dogs").getName(), emptyString );

		}

		TEST_METHOD(deleteFromTableCommand)
		{
			Parser p( d , r );
			string dml = "DELETE FROM Dogs WHERE (Owner == \"Melodie\");";
			p.parse(dml);

			vector<Entry> test;

			test.push_back(Entry("Zipper", 10));
			test.push_back(Entry("Melodie", 10));
			test.push_back(Entry(14));

			vector<Entry*> entryPointers;

			entryPointers.push_back( &test[0] );
			entryPointers.push_back( &test[1] );
			entryPointers.push_back( &test[2] );

			Relation relation;
			p.getRelation("Dogs", relation);

			Assert::IsFalse( relation.hasTuple( entryPointers ) );
		}

		TEST_METHOD(insert)
		{
			testAtts.push_back(Attribute("Name", VARCHAR, 10));
			testAtts.push_back(Attribute("Owner", VARCHAR, 10));
			testAtts.push_back(Attribute("Age", INTEGER));

			keys.push_back(0);
			keys.push_back(2);

			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());

			entries.at(0).push_back(Entry("Abby", 10));
			entries.at(0).push_back(Entry("Amy", 10));
			entries.at(0).push_back(Entry(3));

			d.addRelationToDatabase("Dogs", testAtts, keys);

			d.addTupleToRelation(entries.at(0), "Dogs");

			vector<Entry> newTuple1;

			newTuple1.push_back(Entry("Rockie", 10));
			newTuple1.push_back(Entry("Brain", 10));
			newTuple1.push_back(Entry(7));

			d.addTupleToRelation( newTuple1 , "Dogs");

			vector<Entry*> entryPointers;

			entryPointers.push_back( &newTuple1[0] );
			entryPointers.push_back( &newTuple1[1] );
			entryPointers.push_back( &newTuple1[2] );

			Assert::IsTrue( d.accessRelation( "Dogs" ).hasTuple( entryPointers ) );

		}


		TEST_METHOD(deleteFromTable)
		{
			
			testAtts.push_back(Attribute("Name", VARCHAR, 10));
			testAtts.push_back(Attribute("Owner", VARCHAR, 10));
			testAtts.push_back(Attribute("Age", INTEGER));

	
			keys.push_back(0);
			keys.push_back(2);

			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());

			entries.at(0).push_back(Entry("Abby", 10));
			entries.at(0).push_back(Entry("Amy", 10));
			entries.at(0).push_back(Entry(3));

			entries.at(1).push_back(Entry("Zipper", 10));
			entries.at(1).push_back(Entry("Melodie", 10));
			entries.at(1).push_back(Entry(14));

			d.addRelationToDatabase("Dogs", testAtts, keys);

			d.addTupleToRelation(entries.at(0), "Dogs");
			d.addTupleToRelation(entries.at(1), "Dogs");

			vector<Condition> c3;
	
			c3.push_back(Condition("Owner", EQUALS, Entry("Melodie", 10), NONE, 1));

			Relation dogs = d.deleteFromRelation("Dogs", c3);

			vector<Entry> test;

			test.push_back(Entry("Zipper", 10));
			test.push_back(Entry("Melodie", 10));
			test.push_back(Entry(14));

			vector<Entry*> entryPointers;

			entryPointers.push_back( &test[0] );
			entryPointers.push_back( &test[1] );
			entryPointers.push_back( &test[2] );

			Assert::IsFalse( d.accessRelation( "Dogs" ).hasTuple( entryPointers ) );

		}

		TEST_METHOD(select)
		{
			vector<Condition> c;
			
			c.push_back(Condition("Age", GR, 4, AND, 1));

			Relation relation = d.selection( c, "Dogs");

			Assert::AreEqual( relation.getNumTuples(), 2 );
			
		}

		TEST_METHOD(difference)
		{
			Relation relationB = d.differenceTwoRelation( "Dogs", "More_Dogs" );
			Relation test("test",testAtts,keys);

			d.addRelationToDatabase( test) ;

			vector<vector<Entry>> testEntries;
			testEntries.push_back(vector<Entry>());
			testEntries.push_back(vector<Entry>());
			testEntries.push_back(vector<Entry>());

			testEntries.at(0).push_back(Entry("Zipper", 10));
			testEntries.at(0).push_back(Entry("Melodie", 10));
			testEntries.at(0).push_back(Entry(14));

			testEntries.at(1).push_back(Entry("Bailey", 10));
			testEntries.at(1).push_back(Entry("Davin", 10));
			testEntries.at(1).push_back(Entry(6));

			d.addTupleToRelation(testEntries.at(0), "test");
			d.addTupleToRelation(testEntries.at(1), "test");

			test = d.accessRelation("test");

			Assert::AreEqual( relationB.getEntry(0,0)->getEntryVC(), test.getEntry(0,0)->getEntryVC());
			Assert::AreEqual( relationB.getEntry(1,0)->getEntryVC(), test.getEntry(1,0)->getEntryVC());
		}

		TEST_METHOD(accessAttribute)
		{
			testAtts.push_back(Attribute("Name", VARCHAR, 10));
			testAtts.push_back(Attribute("Owner", VARCHAR, 10));
			testAtts.push_back(Attribute("Age", INTEGER));

	
			keys.push_back(0);
			keys.push_back(2);

			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());

			entries.at(0).push_back(Entry("Abby", 10));
			entries.at(0).push_back(Entry("Amy", 10));
			entries.at(0).push_back(Entry(3));


			entries.at(1).push_back(Entry("Zipper", 10));
			entries.at(1).push_back(Entry("Melodie", 10));
			entries.at(1).push_back(Entry(14));

			entries.at(2).push_back(Entry("Bailey", 10));
			entries.at(2).push_back(Entry("Davin", 10));
			entries.at(2).push_back(Entry(6));
	
			d.addRelationToDatabase("Dogs", testAtts, keys);

			d.addTupleToRelation(entries.at(0), "Dogs");
			d.addTupleToRelation(entries.at(1), "Dogs");
			d.addTupleToRelation(entries.at(2), "Dogs");

			Relation dogs = d.accessRelation("Dogs");
			vector<Attribute> dogAttributes = dogs.getAttributes();
			string name = "Name";

			Assert::AreEqual( (d.accessAttribute( dogAttributes[0].name, "Dogs" ))->name , name);
		}

		TEST_METHOD(unionRelations)
		{

			testAtts.push_back(Attribute("Name", VARCHAR, 10));
			testAtts.push_back(Attribute("Owner", VARCHAR, 10));
			testAtts.push_back(Attribute("Age", INTEGER));

	
			keys.push_back(0);
			keys.push_back(2);

			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());

			entries.at(0).push_back(Entry("Abby", 10));
			entries.at(0).push_back(Entry("Amy", 10));
			entries.at(0).push_back(Entry(3));


			entries.at(1).push_back(Entry("Zipper", 10));
			entries.at(1).push_back(Entry("Melodie", 10));
			entries.at(1).push_back(Entry(14));

			entries.at(2).push_back(Entry("Bailey", 10));
			entries.at(2).push_back(Entry("Davin", 10));
			entries.at(2).push_back(Entry(6));
	
			d.addRelationToDatabase("Dogs", testAtts, keys);

			d.addTupleToRelation(entries.at(0), "Dogs");
			d.addTupleToRelation(entries.at(1), "Dogs");
			d.addTupleToRelation(entries.at(2), "Dogs");

			e2.push_back(vector<Entry>());
			e2.push_back(vector<Entry>());
			e2.push_back(vector<Entry>());

			e2.at(0).push_back(Entry("Tyler", 10));
			e2.at(0).push_back(Entry("Garren", 10));
			e2.at(0).push_back(Entry(5));

			e2.at(1).push_back(Entry("Abby", 10));
			e2.at(1).push_back(Entry("Amy", 10));
			e2.at(1).push_back(Entry(3));

			e2.at(2).push_back(Entry("Dusty", 10));
			e2.at(2).push_back(Entry("Rodger", 10));
			e2.at(2).push_back(Entry(11));

			d.addRelationToDatabase("More_Dogs", testAtts, keys);

			d.addTupleToRelation(e2.at(0), "More_Dogs");
			d.addTupleToRelation(e2.at(1), "More_Dogs");
			d.addTupleToRelation(e2.at(2), "More_Dogs");

			//test set union
			Assert::AreEqual( ( d.unionTwoRelations( "More_Dogs" , "Dogs" ) ).getNumTuples(),
				( d.unionTwoRelations( "Dogs" , "More_Dogs" ) ).getNumTuples() );

		}
			//test set difference
		TEST_METHOD(crossproduct)
		{

			testAtts.push_back(Attribute("Name", VARCHAR, 10));
			testAtts.push_back(Attribute("Owner", VARCHAR, 10));
			testAtts.push_back(Attribute("Age", INTEGER));

	
			keys.push_back(0);
			keys.push_back(2);

			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());

			entries.at(0).push_back(Entry("Abby", 10));
			entries.at(0).push_back(Entry("Amy", 10));
			entries.at(0).push_back(Entry(3));


			entries.at(1).push_back(Entry("Zipper", 10));
			entries.at(1).push_back(Entry("Melodie", 10));
			entries.at(1).push_back(Entry(14));

			entries.at(2).push_back(Entry("Bailey", 10));
			entries.at(2).push_back(Entry("Davin", 10));
			entries.at(2).push_back(Entry(6));
	
			d.addRelationToDatabase("Dogs", testAtts, keys);

			d.addTupleToRelation(entries.at(0), "Dogs");
			d.addTupleToRelation(entries.at(1), "Dogs");
			d.addTupleToRelation(entries.at(2), "Dogs");

			//relation More_Dogs
			e2.push_back(vector<Entry>());
			e2.push_back(vector<Entry>());
			e2.push_back(vector<Entry>());

			e2.at(0).push_back(Entry("Tyler", 10));
			e2.at(0).push_back(Entry("Garren", 10));
			e2.at(0).push_back(Entry(5));

			e2.at(1).push_back(Entry("Abby", 10));
			e2.at(1).push_back(Entry("Amy", 10));
			e2.at(1).push_back(Entry(3));

			e2.at(2).push_back(Entry("Dusty", 10));
			e2.at(2).push_back(Entry("Rodger", 10));
			e2.at(2).push_back(Entry(11));

			d.addRelationToDatabase("More_Dogs", testAtts, keys);

			d.addTupleToRelation(e2.at(0), "More_Dogs");
			d.addTupleToRelation(e2.at(1), "More_Dogs");
			d.addTupleToRelation(e2.at(2), "More_Dogs");


			//test cross product
			Assert::AreEqual( ( d.crossProduct( "More_Dogs" , "Dogs" ) ).getNumTuples(),
				( d.crossProduct( "Dogs" , "More_Dogs" ) ).getNumTuples() );

			//test natural join

		}

		TEST_METHOD(rename)
		{

			testAtts.push_back(Attribute("Name", VARCHAR, 10));
			testAtts.push_back(Attribute("Owner", VARCHAR, 10));
			testAtts.push_back(Attribute("Age", INTEGER));

	
			keys.push_back(0);
			keys.push_back(2);

			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());

			entries.at(0).push_back(Entry("Abby", 10));
			entries.at(0).push_back(Entry("Amy", 10));
			entries.at(0).push_back(Entry(3));


			entries.at(1).push_back(Entry("Zipper", 10));
			entries.at(1).push_back(Entry("Melodie", 10));
			entries.at(1).push_back(Entry(14));

			entries.at(2).push_back(Entry("Bailey", 10));
			entries.at(2).push_back(Entry("Davin", 10));
			entries.at(2).push_back(Entry(6));
	
			d.addRelationToDatabase("Dogs", testAtts, keys);

			d.addTupleToRelation(entries.at(0), "Dogs");
			d.addTupleToRelation(entries.at(1), "Dogs");
			d.addTupleToRelation(entries.at(2), "Dogs");

			Relation dogs = d.accessRelation("Dogs");
			//testing renaming
			vector<string> newAttributeName;
			newAttributeName.push_back("Dog Name");
			newAttributeName.push_back("Owner Name");
			newAttributeName.push_back("Dog age");

			Assert::AreEqual( d.renameAttributes( newAttributeName, dogs.getName() ).getAttributeNames()[0], newAttributeName[0]  );
			Assert::AreEqual( d.renameAttributes( newAttributeName, dogs.getName() ).getAttributeNames()[1], newAttributeName[1]  );
			Assert::AreEqual( d.renameAttributes( newAttributeName, dogs.getName() ).getAttributeNames()[2], newAttributeName[2]  );

			Assert::AreEqual(1,1); //testing test
		}

		TEST_METHOD(update)
		{
			testAtts.push_back(Attribute("Name", VARCHAR, 10));
			testAtts.push_back(Attribute("Owner", VARCHAR, 10));
			testAtts.push_back(Attribute("Age", INTEGER));

	
			keys.push_back(0);
			keys.push_back(2);

			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());

			entries.at(0).push_back(Entry("Abby", 10));
			entries.at(0).push_back(Entry("Amy", 10));
			entries.at(0).push_back(Entry(3));


			entries.at(1).push_back(Entry("Zipper", 10));
			entries.at(1).push_back(Entry("Melodie", 10));
			entries.at(1).push_back(Entry(14));

			entries.at(2).push_back(Entry("Bailey", 10));
			entries.at(2).push_back(Entry("Davin", 10));
			entries.at(2).push_back(Entry(6));

	
			d.addRelationToDatabase("Dogs", testAtts, keys);

			d.addTupleToRelation(entries.at(0), "Dogs");
			d.addTupleToRelation(entries.at(1), "Dogs");
			d.addTupleToRelation(entries.at(2), "Dogs");

			Relation dogs = d.accessRelation( "Dogs");

			vector<string> aa;
			aa.push_back("Age");

			vector<Entry> age;
			age.push_back(Entry(40));

			vector<Condition> c2;
	
			c2.push_back(Condition("Owner", EQUALS, Entry("Melodie", 10), NONE, 1));

			d.update( dogs.getName(), aa, age, c2 );

			vector<Entry> test;

			test.push_back(Entry("Zipper", 10));
			test.push_back(Entry("Melodie", 10));
			test.push_back(Entry(40));

			vector<Entry*> entryPointers;

			entryPointers.push_back( &test[0] );
			entryPointers.push_back( &test[1] );
			entryPointers.push_back( &test[2] );

			Assert::IsTrue( d.accessRelation( "Dogs" ).hasTuple( entryPointers ) );
		}

		TEST_METHOD(naturalJoin)
		{
			testAtts.push_back(Attribute("Name", VARCHAR, 10));
			testAtts.push_back(Attribute("Owner", VARCHAR, 10));
			testAtts.push_back(Attribute("Age", INTEGER));

	
			keys.push_back(0);
			keys.push_back(2);

			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());
			entries.push_back(vector<Entry>());

			entries.at(0).push_back(Entry("Abby", 10));
			entries.at(0).push_back(Entry("Amy", 10));
			entries.at(0).push_back(Entry(3));


			entries.at(1).push_back(Entry("Zipper", 10));
			entries.at(1).push_back(Entry("Melodie", 10));
			entries.at(1).push_back(Entry(14));

			entries.at(2).push_back(Entry("Bailey", 10));
			entries.at(2).push_back(Entry("Davin", 10));
			entries.at(2).push_back(Entry(6));
	
			d.addRelationToDatabase("Dogs", testAtts, keys);

			d.addTupleToRelation(entries.at(0), "Dogs");
			d.addTupleToRelation(entries.at(1), "Dogs");
			d.addTupleToRelation(entries.at(2), "Dogs");

			//relation More_Dogs
			e2.push_back(vector<Entry>());
			e2.push_back(vector<Entry>());
			e2.push_back(vector<Entry>());

			e2.at(0).push_back(Entry("Tyler", 10));
			e2.at(0).push_back(Entry("Garren", 10));
			e2.at(0).push_back(Entry(5));

			e2.at(1).push_back(Entry("Abby", 10));
			e2.at(1).push_back(Entry("Amy", 10));
			e2.at(1).push_back(Entry(3));

			e2.at(2).push_back(Entry("Dusty", 10));
			e2.at(2).push_back(Entry("Rodger", 10));
			e2.at(2).push_back(Entry(11));

			d.addRelationToDatabase("More_Dogs", testAtts, keys);

			d.addTupleToRelation(e2.at(0), "More_Dogs");
			d.addTupleToRelation(e2.at(1), "More_Dogs");
			d.addTupleToRelation(e2.at(2), "More_Dogs");

			 Relation rel = d.naturalJoin( "More_Dogs", "Dogs" );

			 Assert::AreEqual(rel.getNumTuples(), max( d.accessRelation("More_Dogs").getNumTuples(), d.accessRelation("Dogs").getNumTuples() ) );
			 
		}

		TEST_METHOD(selectionCommand)
		{
			Parser p( d , r );
			string dml = "puppies <- select (Age == 1) Dogs;";

			p.parse( dml );

			Relation relation;
			p.getRelation("puppies",relation);

			Assert::AreEqual( relation.getNumTuples() , 1 );
		
		}

		TEST_METHOD(differenceCommand)
		{
			Parser p( d , r );
			string dml = "both_dogsA <- Dogs - More_Dogs;";

			p.parse( dml );

			dml = "both_dogsB <- More_Dogs - Dogs;";
			p.parse( dml );
			Relation relationA;
			p.getRelation("both_dogsA",relationA);

			Relation test("test",testAtts,keys);

			d.addRelationToDatabase( test) ;

			vector<vector<Entry>> testEntries;
			testEntries.push_back(vector<Entry>());
			testEntries.push_back(vector<Entry>());
			testEntries.push_back(vector<Entry>());

			testEntries.at(0).push_back(Entry("Zipper", 10));
			testEntries.at(0).push_back(Entry("Melodie", 10));
			testEntries.at(0).push_back(Entry(14));

			testEntries.at(1).push_back(Entry("Bailey", 10));
			testEntries.at(1).push_back(Entry("Davin", 10));
			testEntries.at(1).push_back(Entry(6));

			d.addTupleToRelation(testEntries.at(0), "test");
			d.addTupleToRelation(testEntries.at(1), "test");

			p.getRelation("test",test);

			Assert::AreEqual( relationA.getEntry(0,0)->getEntryVC(), test.getEntry(0,0)->getEntryVC());
			Assert::AreEqual( relationA.getEntry(1,0)->getEntryVC(), test.getEntry(1,0)->getEntryVC());
		}

		TEST_METHOD(projectionCommand)
		{
			Parser p( d , r );
			string dml = "a <- project (Name, Age) Dogs;";

			p.parse( dml );

			Relation relation;
			p.getRelation("a",relation);

			vector<string> attributes;
			attributes.push_back("Name");
			attributes.push_back("Age");

			Assert::AreEqual(attributes[0], relation.getAttributeNames()[0]);
			Assert::AreEqual(attributes[1], relation.getAttributeNames()[1]); 	

		}

		TEST_METHOD(unionCommand)
		{
			Parser p( d , r );
			string dml = "both_dogsA <- Dogs + More_Dogs;";
			p.parse( dml );

			dml = "both_dogsB <- More_Dogs + Dogs;";
			p.parse( dml );

			Relation relationA;
			p.getRelation("both_dogsA",relationA);
			Relation relationB;
			p.getRelation("both_dogsB",relationB);

			Assert::AreEqual( relationA.getNumTuples() , relationB.getNumTuples() );
		}

		TEST_METHOD(renameCommand)
		{
			Parser p( d , r );
			string dml = "a <- rename (AName, AAge) (project (Name, Age) Dogs);";

			p.parse( dml );

			Relation relation;
			p.getRelation("a",relation);

			vector<string> attributes;
			attributes.push_back("AName");
			attributes.push_back("AAge");

			Assert::AreEqual(attributes[0], relation.getAttributeNames()[0]);
			Assert::AreEqual(attributes[1], relation.getAttributeNames()[1]); 

		}

		TEST_METHOD(insertIntoCommand)
		{
			Parser p( d , r );
			string dml = "INSERT INTO Dogs VALUES FROM (\"Spot\", \"Timmy\", 4);";

			p.parse( dml );

			Relation relation = d.accessRelation( "Dogs" );

			vector<Entry> newTuple1;

			newTuple1.push_back(Entry("Spot", 10));
			newTuple1.push_back(Entry("Timmy", 10));
			newTuple1.push_back(Entry(4));

			vector<Entry*> entryPointers;

			entryPointers.push_back( &newTuple1[0] );
			entryPointers.push_back( &newTuple1[1] );
			entryPointers.push_back( &newTuple1[2] );

			Assert::IsTrue( relation.hasTuple( entryPointers ) );
		}

		TEST_METHOD(dropTableCommand)
		{
			Parser p( d , r );
			string dml = "both_dogsA <- Dogs * More_Dogs";

			p.parse( dml );

			dml = "DROP TABLE both_dogsA";

			p.parse(dml);

			Relation relation;

			Assert::AreEqual( p.getRelation("both_dogsA", relation), -1 );
		}

		TEST_METHOD(crossProductCommand)
		{
			Parser p( d , r );
			string dml = "both_dogsA <- Dogs * More_Dogs";

			p.parse( dml );

			dml = "both_dogsB <- More_Dogs * Dogs";
			p.parse( dml );
			Relation relationA;
			p.getRelation("both_dogsA",relationA);
			Relation relationB;
			p.getRelation("both_dogsB",relationB);


			Assert::AreEqual( relationA.getNumTuples(), relationB.getNumTuples() );
		}

		TEST_METHOD(createTableCommand)
		{
			Parser p( d , r );
			string dml = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";

			p.parse(dml);

			Relation relation = d.accessRelation( "animals" );

			string name = "animals";

			Assert::AreEqual( d.accessRelation( "animals" ).getName(), name );
		}

		TEST_METHOD(writeFileCommand)
		{
			Parser p( d , r );
			string dml = "OPEN Dogs;";
			p.parse(dml);
			dml = "WRITE Dogs;";

			Assert::AreEqual( p.parse(dml), 1);
		}

		TEST_METHOD(closeFileCommand)
		{
			Parser p( d , r );
			string dml = "OPEN Dogs;";
			p.parse(dml);
			dml = "WRITE Dogs;";
			p.parse(dml);
			dml = "CLOSE Dogs;";

			Assert::AreEqual( p.parse(dml), 1);
		}

		TEST_METHOD(openFileCommand)
		{
			Parser p( d , r );
			string dml = "WRITE Dogs;";

			Assert::AreEqual( p.parse(dml), 1);
		}

		TEST_METHOD(showCommand)
		{
			Parser p( d , r );
			string dml = "SHOW Dogs;";

			Assert::AreEqual( p.parse(dml), 1);
		}

		TEST_METHOD(updateCommand)
		{
			Parser p( d , r );
			string dml = "UPDATE Dogs SET Age = 40 WHERE (Owner == \"Melodie\");";

			p.parse(dml);

			Relation relation;
			p.getRelation("Dogs",relation);

			vector<Entry> test;

			test.push_back(Entry("Zipper", 10));
			test.push_back(Entry("Melodie", 10));
			test.push_back(Entry(40));

			vector<Entry*> entryPointers;

			entryPointers.push_back( &test[0] );
			entryPointers.push_back( &test[1] );
			entryPointers.push_back( &test[2] );

			Assert::IsTrue( relation.hasTuple( entryPointers ) );

		}

		TEST_METHOD( parseExit )
		{
			Parser p( d , r );
			string dml = "EXIT;";

			Assert::AreEqual( p.parse( dml ), -2 );
		}

		TEST_METHOD( selectionCommandBad )
		{
			Parser p( d , r );
			string dml = "puppies <- select Age == 1) Dogs;"; // missing opening (

			Assert::AreEqual( p.parse( dml ), -1 );

		}

		TEST_METHOD( differenceCommandBad )
		{
			Parser p( d , r );
			string dml = "both_dogsA <- Dogs - More_Dogsjffjgfjghf";

			Assert::AreEqual( p.parse( dml ), -1 );
		}

		TEST_METHOD( projectionCommandBad )
		{
			Parser p( d , r );
		
			string dml = "a <- project Name, Age Dogs;";

			Assert::AreEqual( p.parse( dml ), -1 );

		}

		TEST_METHOD( renameCommandBad )
		{
			Parser p( d , r );
			string dml = "a <- rename AName, AAge (project (Name, Age) Dogs);";

			Assert::AreEqual( p.parse( dml ), -1 );

			dml = "a <- rena (AName, AAge) (project (Name, Age) Dogs);";

			Assert::AreEqual( p.parse( dml ), -1 );

		}

		TEST_METHOD( insertIntoCommandBad )
		{
			Parser p( d , r );
			string dml = "INSERT INTO Dogs VALUES FORM (\"Spot\", \"Timmy\", 4);";

			Assert::AreEqual( p.parse( dml ), -1 );			
		}

		TEST_METHOD( crossProductCommandBad )
		{
			Parser p( d , r );
			string dml = "both_dogsA <- Dogs ** More_Dogs";

			Assert::AreEqual( p.parse( dml ), -1 );
		}

		TEST_METHOD( createTableCommandBad )
		{
			Parser p( d , r );
			string dml = "CREATE TABLE animals name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";

			Assert::AreEqual( p.parse( dml ), -1 );

			dml = "CREATE TABLE animals (name STRING(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";

			Assert::AreEqual( p.parse( dml ), -1 );
		}

		TEST_METHOD( deleteCommand )
		{
			Parser p( d , r );
			string dml = "DELETE FROM Dogs WHERE (Age == 14);";

			p.parse( dml );

			Relation relation = d.accessRelation( "Dogs" );

			Assert::AreEqual( relation.getNumTuples( ), 2 );

		}
		TEST_METHOD( deleteCommandBad )
		{
			Parser p( d , r );
			string dml = "DELETE FROM Dogs WHREE (Age == 14);";

			Assert::AreEqual( p.parse( dml ), -1 );

			dml = "DELETE FROM Dogs WHERE fhfhfhfh;";

			Assert::AreEqual( p.parse( dml ), -1 );

			dml = "DELETE FORM Dogs WHERE (Age == 14);";

			Assert::AreEqual( p.parse( dml ), -1 );

		}

		TEST_METHOD(addGame)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "INSERT INTO games VALUES FROM (\"earth\",  \"1/13/2014\", \"2:30\", \"soccer\", 1234 );";

			Assert::AreEqual( database.execute( parserCommand ), 1 );

		}

		TEST_METHOD(addPlayer)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "INSERT INTO players VALUES FROM (\"Jimmy\", \"Johns\", 52015875, 1234 );";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}

		TEST_METHOD(addReferee)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "INSERT INTO referees VALUES FROM (\"Zebra\", \"boy\", 78154564, 1234 );";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}

		TEST_METHOD(addSport)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "INSERT INTO sports VALUES FROM (\"soccer\", 1234, \"spring\" );";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}

		TEST_METHOD(addTeam)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "INSERT INTO teams VALUES FROM (\"Firecrakers\", 5678 );";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}

		TEST_METHOD(changeGameLocation)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");


			string parserCommand = "INSERT INTO games VALUES FROM (\"earth\",  \"12014\", \"230\", \"soccer\", 1234 );";

			Assert::AreEqual( database.execute( parserCommand ), 1 );

			parserCommand = "UPDATE games SET location = \"REC\" WHERE (gameID == 1234);";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}

		TEST_METHOD(changeGameTime)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "INSERT INTO games VALUES FROM (\"earth\",  \"12014\", \"230\", \"soccer\", 1234 );";

			Assert::AreEqual( database.execute( parserCommand ), 1 );

			parserCommand = "UPDATE games SET time = \"130\" WHERE (gameID == 1234);";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}

		TEST_METHOD(changeSportSeason)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "INSERT INTO sports VALUES FROM (\"soccer\", 1234, \"spring\" );";

			Assert::AreEqual( database.execute( parserCommand ), 1 );

			parserCommand = "UPDATE sports SET season = \"fall\" WHERE (sportID == 1234);";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}

		TEST_METHOD(displaySportGame)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "newView <- select (sport == \"soccer\") games;";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}

		TEST_METHOD(displaySportsPlayed)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "playerPlays <- select (netID == 858386873) players;";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}

		TEST_METHOD(listNamesOfSports)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "sportName <- project (name) sports;";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}

		TEST_METHOD(removeGame)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "DELETE FROM games WHERE (gameID == 796 );";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}

		TEST_METHOD(removePlayer)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "DELETE FROM players WHERE (netID == 858386873);";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}

		TEST_METHOD(removeReferee)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "DELETE FROM referees WHERE (netID == 4785693);";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}

		TEST_METHOD(removeSport)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "DELETE FROM sports WHERE (sportID == 1234);";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}

		TEST_METHOD(removeTeam)
		{
			DBCell database( r );
			database.execute( "CREATE TABLE games (location VARCHAR(20), date VARCHAR(10), time VARCHAR(10), sport VARCHAR(10), gameID INTEGER ) PRIMARY KEY (gameID);" );
			database.execute( "CREATE TABLE players (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);" );
			database.execute( "CREATE TABLE referees (firstname VARCHAR(20), lastname VARCHAR(20), netID INTEGER, sportID INTEGER ) PRIMARY KEY (netID);");
			database.execute( "CREATE TABLE sports (name VARCHAR(20), sportID INTEGER, season VARCHAR(10)) PRIMARY KEY (sportID);" );
			database.execute( "CREATE TABLE teams (name VARCHAR(20), teamID INTEGER ) PRIMARY KEY (teamID);");

			string parserCommand = "DELETE FROM teams WHERE (teamID == 6846);";

			Assert::AreEqual( database.execute( parserCommand ), 1 );
		}



	};
}