#include "Parser.h"
#include <iostream>
#include <sstream>

#define SUCCESS 1
#define INVALID -1
#define EXIT -2


//Gets a relation from views or from database
Relation Parser::getRelation(string r){

	for(int i = 0; i < views.size(); i++){
		if(views.at(i).getName() == r){
			return views.at(i);
		}
	}

	return database.accessRelation(r);

}

//DONE
//We pass the integer values of the characters so our check is quick
bool Parser::isAlphaNum(int c){

	int ZERO = 48;
	int NINE = 57;

	int A = 65;
	int Z = 90;
	
	int a = 97;
	int z = 122;

	int UNDERSCORE = 95;

	return ( (c >= ZERO && c <= NINE) || (c >= A && c <= Z) || (c >= a && c <= z) || UNDERSCORE);

}

//DONE - NOT TESTED
string Parser::readAlphaNumWord(stringstream& command){

	readWhite(command);

	string result = "";
	char next;

	while(isAlphaNum( command.peek()) ){

		command.get(next);
		result.push_back(next);

	}

	readWhite(command);

	return result;
}

//DONE
void Parser::readWhite(stringstream& command){

	while(command.peek() == ' '){
		command.get();
	}

}

//DONE
int Parser::readSemi(stringstream& command){

	readWhite(command);

	char semi;
	command.get(semi);

	if( semi == ';' ){
		return SUCCESS;
	}

	command.putback(semi);

	return INVALID;

}

//DONE
int Parser::readArrow(stringstream& command){

	readWhite(command);

	char dash;
	char less;

	command.get(less);

	if( less != '<' || command.peek() != '-' ){

		command.putback(less);
		return INVALID;

	}

	command.get(dash);

	return SUCCESS;

}

//DONE
int Parser::parseAttributeList(stringstream& command, vector<string>& attributeNames){

	readWhite(command);

	char open;
	command.get(open);

	if( open != '(' ){
		return INVALID;
	}

	

	char commaOrClose;
	string name;

	

	do{

		readWhite(command);

		name = readAlphaNumWord(command);
		attributeNames.push_back(name);

		readWhite(command);

		command.get(commaOrClose);

	}while(commaOrClose == ',');

	if(commaOrClose != ')'){
		return INVALID;
	}

	return SUCCESS;

}

//DONE
Relation Parser::projection(stringstream& command){

	vector<string> attributeNames;

	if( parseAttributeList(command, attributeNames) < 0 ){
		return Relation();
	}

	Relation r = parseExpr(command);

	if( r.isEmpty() ){
		return r;
	}

	return database.projection(attributeNames, &r);

}

//UNDER CONSTRUCTION
Relation Parser::rename(stringstream& command){

	readWhite(command);

	vector<string> attributeNames;

	if( parseAttributeList(command, attributeNames) < 0){
		return Relation();
	}

	Relation r = parseExpr(command);

	if( r.isEmpty() ){
		return r;
	}

	return database.renameAttributes(attributeNames, &r);

}

//DONE - NOT TESTED
int Parser::parseCommand(stringstream& command){

	string word = readAlphaNumWord(command);
	
	if( word == "OPEN" ){
	
		string relationName = readAlphaNumWord(command);
		
		//Catch problem before execution
		if( readSemi(command) < 0){
			return INVALID;
		}
		
		openFile(relationName);
		
		return SUCCESS;
	
	}else if( word == "CLOSE" ){
	
		string relationName = readAlphaNumWord(command);

		if( closeFile(relationName) < 0 ){
			return INVALID;
		}

		if( readSemi(command) < 0){
			return INVALID;
		}

	}else if( word == "SHOW" ){
	
		string relationName = readAlphaNumWord(command);
		
		//Catch problem before execution
		if( readSemi(command) < 0){
			return INVALID;
		}
	
		cout<< *database.accessRelation(relationName);
	
		return SUCCESS;
	
	}else if( word == "WRITE" ){

		string relationName = readAlphaNumWord(command);
		
		//Catch problem before execution
		if( readSemi(command) < 0){
			return INVALID;
		}

		if( writeFile(relationName) < 0){
			return INVALID;
		}

		return SUCCESS;

	}else if( word == "INSERT" ){

		string into = readAlphaNumWord(command);

		if( into != "INTO" ){
			return INVALID;
		}

		if( insertInto(command) < 0){
			return INVALID;
		}

		return SUCCESS;

	}else if( word == "DELETE" ){

		string from = readAlphaNumWord(command);

		if( from != "FROM" ){
			return INVALID;
		}

		if( deleteFrom(command) < 0){
			return INVALID;
		}

		return SUCCESS;

	}else if( word == "CREATE" ){
		string table = readAlphaNumWord(command);

		if( table != "TABLE" ){
			return INVALID;
		}

		if( createTable(command) < 0){
			return INVALID;
		}

		return SUCCESS;

	}else if( word == "UPDATE" ){

		if( update(command) < 0){
			return INVALID;
		}

		return SUCCESS;

	}else{

		return INVALID;

	}

}

//DONE - NOT DEBUGGED
int Parser::parseQuery(stringstream& command){

	string relationName = readAlphaNumWord(command);

	if( readArrow(command) < 0){
		return INVALID;
	}

	Relation targetRelation = parseExpr(command);

	if( targetRelation.isEmpty() ){
		return INVALID;
	}

	targetRelation.setName(relationName);

	addView(targetRelation);

	return SUCCESS;

}

//DONE - NOT DEBUGGED
Relation Parser::parseExpr(stringstream& command){

	readWhite(command);

	//Parentheses are optional. We ask here, did they put them in?
	bool openParen;

	if(command.peek() == '('){
		openParen = true;
		command.get();
	}

	//Find command it matches to.

	//Could be word, or relation name, or relation name followed by +/-

	string word = readAlphaNumWord(command);

	Relation targetRelation;

	if( word == "project" ){

		targetRelation = projection(command);

		readWhite(command);

		if( openParen && command.peek() != ')' ){
			return Relation();
		}

		command.get();

		return targetRelation;

	}else if( word == "select" ){

		targetRelation = selection(command);

		readWhite(command);

		if( openParen && command.peek() != ')' ){
			return Relation();
		}

		command.get();

		return targetRelation;

	}else if( word == "rename" ){

		targetRelation = rename(command);

		readWhite(command);

		if( openParen && command.peek() != ')' ){
			return Relation();
		}

		command.get();

		return targetRelation;

	}else{

		//At this point we assume what we have is the name of a relation

		string relationA = word;


		if( readSemi(command) > 0 ){

			targetRelation = getRelation(relationA);

			readWhite(command);

			if( openParen && command.peek() != ')' ){
				return Relation();
			}

			command.get();

			return targetRelation;

		}else if( peekAndReadAddition(command) > 0 ){

			string relationB = readAlphaNumWord(command);


			targetRelation = database.unionTwoRelations(relationA, relationB);

			readWhite(command);

			if( openParen && command.peek() != ')' ){
				return Relation();
			}

			command.get();

			return targetRelation;
			
		}else if( peekAndReadSubtraction(command) > 0){

			string relationB = readAlphaNumWord(command);


			targetRelation = database.differenceTwoRelation(relationA, relationB);

			readWhite(command);

			if( openParen && command.peek() != ')' ){
				return Relation();
			}

			command.get();

			return targetRelation;

		}else if( peekAndReadMultiplication(command) > 0){

			string relationB = readAlphaNumWord(command);

			targetRelation = database.crossProduct(relationA, relationB);

			readWhite(command);

			if( openParen && command.peek() != ')' ){
				return Relation();
			}

			command.get();

			return targetRelation;

		}else{

			//Only valid operation left is JOIN

			string join = readAlphaNumWord(command);

			if( join != "JOIN" ){
				return Relation();
			}

			string relationB = readAlphaNumWord(command);
		

			targetRelation = database.naturalJoin(relationA, relationB);

			readWhite(command);

			if( openParen && command.peek() != ')' ){
				return Relation();
			}

			command.get();

			return targetRelation;

		}


	}


}

int Parser::parse(string s){

	if(s == "EXIT"){
		return EXIT;
	}

	stringstream command;
	command>>s;
	
	//Try to parse it as a command - if it returns error, then we continue
	if(parseCommand(command) > 0){
		
		return SUCCESS;
	
	}

	//Restore the command
	command.clear();
	command>>s;

	if( parseQuery(command) > 0 ){
		return SUCCESS;
	}

	return INVALID;
}



























