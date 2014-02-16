#include "Parser.h"


#define SUCCESS 1
#define INVALID -1
#define EXIT -2


//luin.uial@gmail.com

int Parser::writeFile( string relationName ){

	Relation r = database.accessRelation(relationName);

	vector<Attribute> atts = r.getAttributes();

	vector<vector<Entry*>> table = r.getAllEntries();

	string filename = relationName;
	filename = filename + ".db";

	ofstream file;
	file.open( filename );

	string header = "CREATE TABLE " + r.getName() + '(';

	for(int i = 0; i < atts.size(); i++){

		header = header + atts.at(i).name + ' ';

		header = header + (atts.at(i).t == INTEGER ? "INTEGER" : "VARCHAR");

		if(i != atts.size() - 1){
			header = header + ',';
		}

	}

	header = header + ')' + " PRIMARY KEY (";

	vector<int> keys = r.getKeys();

	for(int i = 0; i < keys.size(); i++){

		header = header + atts.at(keys.at(i)).name;

		if(i != keys.size() - 1){
			header = header + ',';
		}

	}

	header = header + ");\n";

	file << header;

	int rowSize = atts.size();

	for(int i = 0; i < table.size(); i++){

		string entry = "INSERT INTO " + relationName + " VALUES FROM (";

		for(int j = 0; j < rowSize; j++){

			bool flag = atts.at(j).t == VARCHAR;

			if(flag){
				entry = entry + '"';
			}

			Entry* thisEntry = table.at(i).at(j);
			string t;


			if(thisEntry->isInt()){
				t = thisEntry->getEntryI();
			}else{
				t = thisEntry->getEntryVC();
			}

			entry = entry + t;

			if( j != rowSize - 1 ){
				entry = entry + ',';
			}

		}

		entry = entry + ");\n";

		file << entry;
	}

	//I'm not sure how this could fail
	return SUCCESS;
}

int Parser::openFile( string relationName ){

	string line;

	string filename = relationName;

	filename = filename + ".db";

	ifstream file( filename );

	if( file.is_open() ){

		while( getline( file, line ) ){

			parse(line);

		}
		file.close();
	}else{
		//file did not open
		return INVALID;
	}


	return SUCCESS;
}

int Parser::closeFile( string name ){

	string filename = name + ".db";

	fstream f(name);

	f.close();

}

//Gets a relation from views or from database
Relation Parser::getRelation( string r ){

	for ( unsigned i = 0; i < views.size( ); i++ ){
		if ( views.at( i ).getName( ) == r ){
			return views.at( i );
		}
	}

	return database.accessRelation( r );

}

//DONE
//We pass the integer values of the characters so our check is quick
bool Parser::isAlphaNum( int c ){

	return (isAlpha(c) || isNum(c));

}

bool Parser::isAlpha( int c){

	int A = 65;
	int Z = 90;

	int a = 97;
	int z = 122;

	int UNDERSCORE = 95;

	return ( c >= A && c <= Z ) || ( c >= a && c <= z ) || c == UNDERSCORE;

}

bool Parser::isNum( int c){

	int ZERO = 48;
	int NINE = 57;

	return (c >= ZERO && c <= NINE );

}

//DONE - NOT TESTED
string Parser::readAlphaNumWord( stringstream& command ){

	readWhite( command );

	string result = "";
	char next;

	while ( isAlphaNum( command.peek( ) ) ){

		command.get( next );
		result.push_back( next );

	}

	readWhite( command );

	return result;
}

//DONE
void Parser::readWhite( stringstream& command ){

	while ( command.peek( ) == ' ' ){
		command.get( );
	}

}

//DONE
int Parser::readSemi( stringstream& command ){

	readWhite( command );

	char semi;
	command.get( semi );

	if ( semi == ';' ){
		return SUCCESS;
	}

	command.putback( semi );

	return INVALID;

}

//DONE
int Parser::readArrow( stringstream& command ){

	readWhite( command );

	char dash;
	char less;

	command.get( less );

	if ( less != '<' || command.peek( ) != '-' ){

		command.putback( less );
		return INVALID;

	}

	command.get( dash );

	return SUCCESS;

}

//DONE
int Parser::parseAttributeList( stringstream& command, vector<string>& attributeNames ){

	readWhite( command );

	char open;
	command.get( open );

	if ( open != '(' ){
		return INVALID;
	}

	char commaOrClose;
	string name;

	do{

		readWhite( command );

		name = readAlphaNumWord( command );
		attributeNames.push_back( name );

		readWhite( command );

		command.get( commaOrClose );

	} while ( commaOrClose == ',' );

	if ( commaOrClose != ')' ){
		return INVALID;
	}

	return SUCCESS;

}


// DONE - not tested
int Parser::deleteFrom( stringstream& command ) {

	// Get the relation's name
	string relationName = readAlphaNumWord( command );

	// Make sure the WHERE keyword is there
	string whereKeyWord = readAlphaNumWord( command );

	if ( whereKeyWord != "WHERE" ) {
		return INVALID;
	}

	// Get the conditions that will be used by the delete function
	vector<Condition> deleteConditions;

	if( parseConditions(command, deleteConditions) < 0 ){
		return INVALID;
	}

	// Call the delete function on the relation
	database.deleteFromRelation( relationName, deleteConditions );

	return SUCCESS;
}


//DONE - needs testing
Entry readLiteral( stringstream& command ) {
	Entry nextEntry;
	
	char nextChar = command.peek( );

	// If the literal is a string
	if ( nextChar == '\"' ) {
		string stringLiteral = "";

		// keep reading characters into the string until the closing quotes
		while ( command.peek( ) != '\"' ) {
			stringLiteral += command.get( );
		}

		nextEntry = Entry( stringLiteral );
	}

	// if the literal is an integer
	else if ( isdigit( nextChar ) ) {
		string intLiteral = "";

		// read all of the digits into a string
		while ( isdigit( command.peek( ) ) ) {
			intLiteral += command.get( );
		}

		// convert the string into an int
		int actualIntLiteral = stoi( intLiteral );

		nextEntry = Entry( actualIntLiteral );
	}

	return nextEntry;
}

Entry Parser::readLiteral( stringstream& command ){

	int a; 

	if( parseInteger(command, a) < 0 ){

		return Entry( readAlphaNumWord(command) );

	}else{
		return Entry(a);
	}


}


// Done, for sure needs testing -------------------------------------should this check that the tuple has the right attributes for the relation or should database check?
int Parser::insertInto( stringstream& command ) {

	// Get the target Relation name
	string relationName = readAlphaNumWord(command);



	// Read and verify the values key word.
	string valuesKeyWord = readAlphaNumWord( command );
	if ( valuesKeyWord != "VALUES" ) {
		return INVALID;
	}

	// Read and verify the from key word.
	string fromKeyWord = readAlphaNumWord( command );
	if ( fromKeyWord != "FROM" ) {
		return INVALID;
	}

	readWhite( command );

	char parenthesis = command.peek( );

	if ( parenthesis == '(' ) {
		command.get( );

		vector<Entry> tuple;
		Entry helperEntry;
		// ... needs to read a tuple
		// keep reading literals until there is a ')'
		while ( command.peek( ) != ')' ) {
			helperEntry = readLiteral( command );
			//------------------------------------------should this check to see if the entry was formatted bad?
			tuple.push_back( Entry(helperEntry) );
			
			// consume the comma if there is one
			if ( command.peek( ) == ',' ) {
				command.get( );
			}
		}

		char close;
		command.get( close );

		if( close != ')' ){
			return INVALID;
		}

		database.addTupleToRelation( tuple, database.accessRelation(relationName) );
	}
	else {

		// Read and verify the relation key word
		string relationKeyWord = readAlphaNumWord( command );
		if ( relationKeyWord != "RELATION" ) {
			return INVALID;
		}

		// Get the target relation
		Relation whatToReadFrom = parseExpr( command );

		if( whatToReadFrom.isEmpty() ){
			return INVALID;
		}

		//Can we not just call union? Does that command do something different? - Cameron
		database.insertIntoFromRelation( database.accessRelation(relationName), whatToReadFrom );
	}

	return SUCCESS;
}


// DONE - not tested
Relation Parser::crossProduct( stringstream& command ) {
	
	// Get the first relation
	Relation relationA = parseExpr( command );

	// Make sure it is not empty
	if ( relationA.isEmpty( ) ) {
		return relationA;
	}

	// Get the second relation
	Relation relationB = parseExpr( command );

	// Make sure it is not empty
	if ( relationB.isEmpty( ) ) {
		return relationB;
	}

	// Return the result
	return database.crossProduct( relationA, relationB );
}


// DONE - not tested
Relation Parser::difference( stringstream& command ) {
	
	// Get the first relation
	Relation relationA = parseExpr( command );

	// Make sure it is not empty
	if ( relationA.isEmpty( ) ) {
		return relationA;
	}

	// Get the second relation
	Relation relationB = parseExpr( command );

	// Make sure it is not empty
	if ( relationB.isEmpty( ) ) {
		return relationB;
	}

	// Return the result
	return database.differenceTwoRelation( relationA, relationB );
}


//DONE
Relation Parser::projection( stringstream& command ){

	vector<string> attributeNames;

	if ( parseAttributeList( command, attributeNames ) < 0 ){
		return Relation( );
	}

	Relation r = parseExpr( command );

	if ( r.isEmpty( ) ){
		return r;
	}

	return database.projection( attributeNames, r );

}

//TODO
Relation Parser::rename( stringstream& command ){

	readWhite( command );

	vector<string> attributeNames;

	if ( parseAttributeList( command, attributeNames ) < 0 ){
		return Relation( );
	}

	Relation r = parseExpr( command );

	if ( r.isEmpty( ) ){
		return r;
	}

	return database.renameAttributes( attributeNames, r );

}

//DONE - NOT TESTED
int Parser::parseCommand( stringstream& command ){

	string word = readAlphaNumWord( command );

	if ( word == "OPEN" ){

		string relationName = readAlphaNumWord( command );

		//Catch problem before execution
		if ( readSemi( command ) < 0 ){
			return INVALID;
		}

		openFile( relationName );

		return SUCCESS;

	}
	else if ( word == "CLOSE" ){

		string relationName = readAlphaNumWord( command );

		if ( closeFile( relationName ) < 0 ){
			return INVALID;
		}

		if ( readSemi( command ) < 0 ){
			return INVALID;
		}

		return SUCCESS;

	}
	else if ( word == "SHOW" ){

		string relationName = readAlphaNumWord( command );

		//Catch problem before execution
		if ( readSemi( command ) < 0 ){
			return INVALID;
		}

		cout << *database.accessRelation( relationName );

		return SUCCESS;

	}
	else if ( word == "WRITE" ){

		string relationName = readAlphaNumWord( command );

		//Catch problem before execution
		if ( readSemi( command ) < 0 ){
			return INVALID;
		}

		if ( writeFile( relationName ) < 0 ){
			return INVALID;
		}

		return SUCCESS;

	}
	else if ( word == "INSERT" ){

		string into = readAlphaNumWord( command );

		if ( into != "INTO" ){
			return INVALID;
		}

		if ( insertInto( command ) < 0 ){
			return INVALID;
		}

		return SUCCESS;

	}
	else if ( word == "DELETE" ){

		string from = readAlphaNumWord( command );

		if ( from != "FROM" ){
			return INVALID;
		}

		if ( deleteFrom( command ) < 0 ){
			return INVALID;
		}

		return SUCCESS;

	}
	else if ( word == "CREATE" ){
		string table = readAlphaNumWord( command );

		if ( table != "TABLE" ){
			return INVALID;
		}

		if ( createTable( command ) < 0 ){
			return INVALID;
		}

		return SUCCESS;

	}
	else if ( word == "UPDATE" ){

		if ( update( command ) < 0 ){
			return INVALID;
		}

		return SUCCESS;

	}
	else{

		return INVALID;

	}

}

//DONE - NOT DEBUGGED
int Parser::parseQuery( stringstream& command ){

	string relationName = readAlphaNumWord( command );

	if ( readArrow( command ) < 0 ){
		return INVALID;
	}

	Relation targetRelation = parseExpr( command );

	if ( targetRelation.isEmpty( ) ){
		return INVALID;
	}

	targetRelation.setName( relationName );

	addView( targetRelation );

	return SUCCESS;

}


//DONE
int Parser::peekAndReadAddition( stringstream& command ) {

	readWhite( command );

	char plus;
	plus = command.peek( );

	if ( plus != '+' ) {
		return INVALID;
	}

	command.get( );

	return SUCCESS;

}

//DONE
int Parser::peekAndReadSubtraction( stringstream& command ) {

	readWhite( command );

	char sub;
	sub = command.peek( );

	if ( sub != '-' ){ // changed plus to sub, copy and paste error?
		return INVALID;
	}

	command.get( );

	return SUCCESS;

}

//DONE
int Parser::peekAndReadMultiplication( stringstream& command ){

	readWhite( command );

	char mult;
	mult = command.peek( );

	if ( mult != '*' ){
		return INVALID;
	}

	command.get( );

	return SUCCESS;

}

int Parser::readOperator( stringstream& command, Operation& o ){

	char c;
	command.get( c );

	switch ( c ){

	case ( '=' ) :

		command.get( c );
		if ( c != '=' ){
			return INVALID;
		}
		else{
			o = EQUALS;
			return SUCCESS;
		}
		break;

	case ( '!' ) :

		command.get( c );
		if ( c != '=' ){
			return INVALID;
		}
		else{
			o = NEQ;
			return SUCCESS;
		}
		break;

	case ( '<' ) :

		c = command.peek( );

		if ( c != '=' ){
			o = LE;
		}
		else{
			o = LEQ;
		}
		break;

	case ( '>' ) :

		c = command.peek( );

		if ( c != '=' ){
			o = GR;
		}
		else{
			o = GREQ;
		}
		break;

	default:
		return INVALID;


	}

	return INVALID;

}

//TODO
//Put an integer from command into 'i'. Return invalid if method fails
//IF THE METHOD FAILS THIS FUNCTION MUST RETURN COMMAND TO ITS INITIAL STATE
int Parser::parseInteger( stringstream& command, int& arg ){

	vector<char> chars;

	//push back until we find something not an int
	while( isNum(command.peek()) ){
		chars.push_back( command.get() );
	}

	if( isAlpha(command.peek() ) ){

		for(int i = chars.size() - 1; i >= 0; i--){

			command.putback(chars.at(i));

		}

		return INVALID;
	}else{

		string a = "";
		for(int i = 0; i < chars.size(); i++){
			a.push_back(chars.at(i));
		}

		stringstream ss;
		ss<<a;
		ss>>arg;

		return SUCCESS;
	}

	

}


int Parser::findConnector( stringstream& copy, Connector c, int paren){

	readWhite(copy);

	char next;

	copy.get(next);

	while(next == ')' || next == ' '){
		//if it was a parentheses, keep track to see if we hit the end of the condition list
		if(next == ')'){
			paren--;

			if(paren == 0){
				c = NONE;
				return SUCCESS;
			}

		}

		copy.get(next);
	}

	if(next == '&'){
		copy.get(next);

		if(next == '&'){

			c = AND;
			return SUCCESS;
		}else{
			return INVALID;
		}

	}else if(next == '|'){

		copy.get(next);

		if(next == '|'){
			c = OR;
			return SUCCESS;
		}else{
			return INVALID;
		}

	}else{
		return INVALID;
	}

}

//UNDER CONSTRUCTION
int Parser::parseCondition( stringstream& localCommand, int paren, Condition& condition ){

	readWhite( localCommand );

	bool firstIsLit = false;
	bool firstIsStr = false;
	bool secondIsLit = false;
	bool secondIsStr = false;

	string first;
	int firstI;
	string second;
	int secondI;

	Entry a;
	Entry b;

	char next;

	//Read first word/literal
	next = localCommand.peek( );

	//Check if the string starts with a quote. If it does it is a literal string
	if ( next == '"' ){
		firstIsLit = true;
		firstIsStr = true;
		localCommand.get( );
		first = readAlphaNumWord( localCommand );
		a.setVC(first);
	}
	else{

		//If not, it could either be a literal integer, or it is an attribute

		if ( parseInteger( localCommand, firstI ) < 0 ){
			//parseInteger FAILED - it is attribute

			first = readAlphaNumWord( localCommand );
		}else{
			//parseInteger SUCCESS - it is int

			firstIsLit = true;
			a.setInt(firstI);
		}

	}

	if ( firstIsStr ){

		localCommand.get( next );

		if ( next != '"' ){
			return INVALID;
		}

	}

	readWhite( localCommand );

	//Read operator
	Operation o;

	if ( readOperator( localCommand, o ) < 0 ){
		INVALID;
	}

	readWhite( localCommand );

	next = localCommand.peek( );

		//Check if the string starts with a quote. If it does it is a literal string
	if ( next == '"' ){
		secondIsLit = true;
		secondIsStr = true;
		localCommand.get( );
		first = readAlphaNumWord( localCommand );
		a.setVC(second);
	}
	else{

		//If not, it could either be a literal integer, or it is an attribute

		if ( parseInteger( localCommand, secondI ) < 0 ){
			//parseInteger FAILED - it is attribute

			second = readAlphaNumWord( localCommand );
		}else{
			//parseInteger SUCCESS - it is int

			secondIsLit = true;
			a.setInt(secondI);
		}

	}

	if ( secondIsStr ){

		localCommand.get( next );

		if ( next != '"' ){
			return INVALID;
		}

	}

	Connector conn = NONE;

	//stringstream copy construtor is private
	//this should work
	stringstream copy;
	copy <<localCommand.rdbuf();

	if( findConnector(copy, conn, paren) < 0 ){
		return INVALID;
	}

	if ( firstIsLit ){

		if ( secondIsLit ){
			//TWO LITERALS
			
			condition = Condition(a, o, b, conn, paren);
		}else{
			condition = Condition(a, o, second, conn, paren);
		}

	}
	else if ( secondIsLit ){
		//SECOND ONLY IS LITERAL
		condition = Condition(first, o, b, conn, paren);
	}
	else{
		//NONE IS LITERAL
		condition = Condition(first, o, second, conn, paren);
	}

}

int Parser::parseConditions( stringstream& command, vector<Condition>& conditions ){

	//Redefinition of conditions
	//vector<Condition> conditions;

	readWhite( command );

	int paren = 0;

	//Read in parentheses and increment paren

	char next;
	command.get( next );

	if ( next != '(' ){
		return INVALID;
	}
	else{
		++paren;
	}


	//Start of main loop - while we don't get to the end of parentheses
	while ( paren > 0 ){

		//Read in a (Open Parentheses) OR (name OR string) Operator (name OR string) Connector

		Condition c;

		readWhite( command );

		command.get( next );

		if ( next == '(' ){
			++paren;
		}
		else{

			if( parseCondition(command, paren, c) < 0 ){
				return INVALID;
			}

			conditions.push_back(Condition(c));
		}

	}

	//if paren == 0, we're done

	return SUCCESS;
}

//DONE - NOT DEBUGGED
Relation Parser::parseExpr( stringstream& command ){

	readWhite( command );

	//Parentheses are optional. We ask here, did they put them in?
	bool openParen;

	if ( command.peek( ) == '(' ){
		openParen = true;
		command.get( );
	}

	//Find command it matches to.

	//Could be word, or relation name, or relation name followed by +/-

	string word = readAlphaNumWord( command );

	Relation targetRelation;

	if ( word == "project" ){

		targetRelation = projection( command );

		readWhite( command );

		if ( openParen && command.peek( ) != ')' ){
			return Relation( );
		}

		command.get( );

		return targetRelation;

	}
	else if ( word == "select" ){

		targetRelation = selection( command );

		readWhite( command );

		if ( openParen && command.peek( ) != ')' ){
			return Relation( );
		}

		command.get( );

		return targetRelation;

	}
	else if ( word == "rename" ){

		targetRelation = rename( command );

		readWhite( command );

		if ( openParen && command.peek( ) != ')' ){
			return Relation( );
		}

		command.get( );

		return targetRelation;

	}
	else{

		//At this point we assume what we have is the name of a relation

		string relationA = word;


		if ( readSemi( command ) > 0 ){

			targetRelation = getRelation( relationA );

			readWhite( command );

			if ( openParen && command.peek( ) != ')' ){
				return Relation( );
			}

			command.get( );

			return targetRelation;

		}
		else if ( peekAndReadAddition( command ) > 0 ){

			string relationB = readAlphaNumWord( command );


			targetRelation = database.unionTwoRelations( relationA, relationB );

			readWhite( command );

			if ( openParen && command.peek( ) != ')' ){
				return Relation( );
			}

			command.get( );

			return targetRelation;

		}
		else if ( peekAndReadSubtraction( command ) > 0 ){

			string relationB = readAlphaNumWord( command );


			targetRelation = database.differenceTwoRelation( relationA, relationB );

			readWhite( command );

			if ( openParen && command.peek( ) != ')' ){
				return Relation( );
			}

			command.get( );

			return targetRelation;

		}
		else if ( peekAndReadMultiplication( command ) > 0 ){

			string relationB = readAlphaNumWord( command );

			targetRelation = database.crossProduct( relationA, relationB );

			readWhite( command );

			if ( openParen && command.peek( ) != ')' ){
				return Relation( );
			}

			command.get( );

			return targetRelation;

		}
		else{

			//Only valid operation left is JOIN

			string join = readAlphaNumWord( command );

			if ( join != "JOIN" ){
				return Relation( );
			}

			string relationB = readAlphaNumWord( command );


			targetRelation = database.naturalJoin( relationA, relationB );

			readWhite( command );

			if ( openParen && command.peek( ) != ')' ){
				return Relation( );
			}

			command.get( );

			return targetRelation;

		}


	}


}

int Parser::parse( string s ){

	if ( s == "EXIT" ){
		return EXIT;
	}

	stringstream command;
	command >> s;

	//Try to parse it as a command - if it returns error, then we continue
	if ( parseCommand( command ) > 0 ){

		return SUCCESS;

	}

	//Restore the command
	command.clear( );
	command >> s;

	if ( parseQuery( command ) > 0 ){
		return SUCCESS;
	}

	return INVALID;
}


// DONE - not tested
Relation Parser::selection( stringstream& command ) {

	// Parse and get the conditions
	vector<Condition> conditions;

	// If no conditions then return empty Relation
	if ( parseConditions(command, conditions) < 0 ) {
		return Relation( );
	}

	// Get the target relation
	Relation targetRelation = parseExpr( command );

	// If the relation is empty then return the empty relation
	if ( targetRelation.isEmpty( ) ) {
		return targetRelation;
	}

	// return the result of the selection operation
	return database.selection( conditions, targetRelation );


}


// DONE - not tested
Relation Parser::relationUnion( stringstream& command ) {

	// Get the first relation
	Relation relationA = parseExpr( command );

	// Make sure it is not empty
	if ( relationA.isEmpty( ) ) {
		return relationA;
	}

	// Get the second relation
	Relation relationB = parseExpr( command );

	// Make sure it is not empty
	if ( relationB.isEmpty( ) ) {
		return relationB;
	}

	// Return the result
	return database.unionTwoRelations( relationA, relationB );

}
