#include "DBCell.h"
#include <iostream>

DBCell db;

void execute( string s ){
	if ( db.execute(s) < 0 ){
		
		cout<<"Invalid Command\n" << s <<'\n';
	
	}
}

int main(){

	

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

	dml = "old_dogs <- select (years > 8) dogs;";
	execute(dml);

	dml = "SHOW old_dogs;";
	execute(dml);

	dml = "cats_or_dogs <- dogs + (select (kind == \"cat\") animals);";
	execute(dml);

	dml = "SHOW cats_or_dogs;";
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

	dml = "	WRITE animals;";
	execute(dml);

	dml = "CLOSE animals;";
	execute(dml);

	dml = "EXIT;";
	execute(dml);

	return 1;
}