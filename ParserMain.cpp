/*
	This main shows example input and output. An example output file for this
	can be found in animals.db in the same folder as the main source code.
	After the main finishes its example, it remains open as a command line
	interface for the user to use to perform their own database functions.
*/

#include "DBCell.h"
#include <iostream>

DBCell* db;

void outputResult( vector<vector<string>>& r ){

	for(int i = 0; i < r.size(); ++i){

		for(int j = 0; j < r.at(i).size(); ++j){

			cout<<r.at(i).at(j)<<' ';

		}

		cout<<'\n';
	}

}

void readInput(){

	string line = "";

	cout<<"\n\n";

	do{

		cout<<"Enter a dml command:\n";
		cout<<">:";
	line = "";

	string word;

	cin >> word;

	while(word.at(word.size() - 1) != ';'){

		line = line + word + ' ';

		cin>>word;
	}

	line = line + word;

	if( db->execute(line) < 0 ){
		cout << "ERROR in:\n" << line <<'\n';
	}

	}while(line != "EXIT;" && line != "EXIT; " && line != "EXIT;\n");

}

void execute( string s ){
	int t = db->execute(s);
	if ( t < 0 ){
		
		if( t == -2 ){
			return;
		}

		cout<<"Invalid Command\n" << s <<'\n';
	
	}
}

int main(){

	/*
	string dml = "OPEN animals;";
	execute(dml);

	dml = "SHOW animals;";
	execute(dml);
	*/
	vector<vector<string>> result;

	db = new DBCell(result);
	
	string dml = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind)";
	execute(dml);

	dml = "INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);";
	execute(dml);
	dml = "INSERT INTO animals VALUES FROM (\"Spot\", \"dog\", 10);";
	execute(dml);
	dml = "INSERT INTO animals VALUES FROM (\"Snoopy\", \"dog\", 3);";
	execute(dml);
	dml = "INSERT INTO animals VALUES FROM (\"Tweety\", \"bird\", 1);";
	execute(dml);
	dml = "INSERT INTO animals VALUES FROM (\"Joe\", \"bird\", 2);";
	execute(dml);

	dml = "CREATE TABLE age_rhyme (years INTEGER, rhyme VARCHAR(20)) PRIMARY KEY (years, rhyme)";
	execute(dml);

	dml = "INSERT INTO age_rhyme VALUES FROM (4, \"Furry\");";
	execute(dml);
	dml = "INSERT INTO age_rhyme VALUES FROM (10, \"Terrible\");";
	execute(dml);
	dml = "INSERT INTO age_rhyme VALUES FROM (3, \"Threatening\");";
	execute(dml);
	dml = "INSERT INTO age_rhyme VALUES FROM (1, \"Only\");";
	execute(dml);
	dml = "INSERT INTO age_rhyme VALUES FROM (2, \"Timely\");";
	execute(dml);

	dml = "SHOW animals;";
	execute(dml);

	dml = "SHOW age_rhyme;";
	execute(dml);

	dml = "b <- animals JOIN age_rhyme;";
	execute(dml);

	dml = "SHOW b;";
	execute(dml);

	dml = "CREATE TABLE store (name VARCHAR(20), price INTEGER) PRIMARY KEY (name, price)";
	execute(dml);

	dml = "INSERT INTO store VALUES FROM (\"PuppyStore\", 400);";
	execute(dml);

	dml = "INSERT INTO store VALUES FROM (\"Farm\", 100);";
	execute(dml);

	dml = "SHOW animals;";
	execute(dml);
	
	dml = "SHOW store;";
	execute(dml);

	dml = "dogs <- select (kind == \"dog\") animals;";
	execute(dml);
	
	dml = "SHOW dogs;";
	execute(dml);

	dml = "UPDATE animals SET years = 20 WHERE (kind == \"cat\");";
	execute(dml);

	dml = "SHOW animals;";
	execute(dml);

	dml = "old_dogs <- select (years > 8) dogs;";
	execute(dml);

	dml = "SHOW old_dogs;";
	execute(dml);

	dml = "cats_or_dogs <- dogs + (select (kind == \"cat\") animals);";
	execute(dml);

	dml = "SHOW cats_or_dogs;";
	execute(dml);

	dml = "cats <- cats_or_dogs - dogs;";
	execute(dml);

	dml = "SHOW cats;";
	execute(dml);

	dml = "CREATE TABLE species (kind VARCHAR(10)) PRIMARY KEY (kind);";
	execute(dml);

	dml = "INSERT INTO species VALUES FROM RELATION project (kind) animals;";
	execute(dml);

	dml = "SHOW species;";
	execute(dml);

	dml = "a <- rename (aname, akind) (project (name, kind) animals);";
	execute(dml);

	dml = "SHOW a;";
	execute(dml);

	dml = "common_names <- project (name) (select (aname == name && akind != kind) (a * animals));";
	execute(dml);

	dml = "SHOW common_names;";
	execute(dml);
	
	dml = "answer <- common_names;";
	execute(dml);

	dml = "SHOW answer;";
	execute(dml);

	dml = "DELETE FROM animals WHERE (years < 5);";
	execute(dml);

	dml = "SHOW animals;";
	execute(dml);

	dml = "WRITE animals;";
	execute(dml);

	dml = "CLOSE animals;";
	execute(dml);

	dml = "EXIT;";
	execute(dml);
	
	readInput();

	return 1;
}