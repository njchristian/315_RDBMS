#include "DBCell.h"
#include <iostream>

int main(){

	DBCell db;

	string dml = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind)";
	
	if ( db.execute(dml) < 0 ){
		
		cout<<"Invalid Command\n";
	
	}else{
		cout<<"Command May Have Worked\n";
	}
	

}