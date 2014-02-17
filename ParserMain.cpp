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

	dml = "SHOW animals;";
	execute(dml);
	
	return 1;
}