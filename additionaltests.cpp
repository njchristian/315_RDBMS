// additional tests to add to unit test

// natural join fails and the first half of projection fails (second half works even though it is commented out)

		TEST_METHOD( parseExit )
		{
			Parser p( d );
			string dml = "EXIT;";

			Assert::AreEqual( p.parse( dml ), -2 );
		}

		TEST_METHOD( naturalJoinCommandBad )
		{
			Parser p( d );

			string dml = "CREATE TABLE DogsAgain (Name VARCHAR(20), Owner VARCHAR(20), Age INTEGER) PRIMARY KEY (Name, Age);";
			p.parse( dml );

			dml = "INSERT INTO DogsAgain VALUES FROM (\"Abby\", \"Amy\", 3);";
			p.parse( dml );
			dml = "INSERT INTO DogsAgain VALUES FROM (\"Dusty\", \"Rodger\", 11);";
			p.parse( dml );
			dml = "INSERT INTO DogsAgain VALUES FROM (\"Tyler\", \"Gerren\", 5);";
			p.parse( dml );
			dml = "INSERT INTO DogsAgain VALUES FROM (\"Tweety\", \"Some Girl\", 1);";
			p.parse( dml );
			dml = "INSERT INTO DogsAgain VALUES FROM (\"Joe\", \"ADude\", 2);";
			p.parse( dml );
			dml = "Many <- DogsAgain JONI Dogs;"; // spelled join wrong to test invalid check

			

			Assert::AreEqual( p.parse( dml ), -1 );
		}

		TEST_METHOD( selectionCommandBad )
		{
			Parser p( d );
			string dml = "puppies <- select Age == 1) Dogs;"; // missing opening (

			Assert::AreEqual( p.parse( dml ), -1 );

		}

		TEST_METHOD( differenceCommandBad )
		{
			Parser p( d );
			string dml = "both_dogsA <- Dogs - More_Dogsjffjgfjghf";

			Assert::AreEqual( p.parse( dml ), -1 );
		}

		TEST_METHOD( projectionCommandBad )
		{
			Parser p( d );
			string dml = "a <- project (Name, Ega) Dogs;";

			Assert::AreEqual( p.parse( dml ), -1 ); // is returning 1 instead of -1

			//dml = "a <- project Name, Age Dogs;";

			//Assert::AreEqual( p.parse( dml ), -1 );

		}