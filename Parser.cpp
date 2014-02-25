#include "Parser.h"



//TAKE IN MULTIPLE WORD ATTRIBUTE NAMES

int Parser::writeFile( string relationName ) {

	Relation r = database.accessRelation( relationName );

	vector<Attribute> atts = r.getAttributes( );

	vector<vector<Entry*>> table = r.getAllEntries( );

	string filename = relationName;
	filename = filename + ".db";

	ofstream file;
	file.open( filename );

	string header = "CREATE TABLE " + r.getName( ) + '(';

	for ( unsigned i = 0; i < atts.size( ); i++ ) {

		header = header + atts.at( i ).name + ' ';

		header = header + ( atts.at( i ).t == INTEGER ? "INTEGER" : "VARCHAR(20)" );

		if ( i != atts.size( ) - 1 ) {
			header = header + ',';
		}

	}

	header = header + ')' + " PRIMARY KEY (";

	vector<int> keys = r.getKeys( );

	for ( unsigned i = 0; i < keys.size( ); i++ ) {

		header = header + atts.at( keys.at( i ) ).name;

		if ( i != keys.size( ) - 1 ) {
			header = header + ',';
		}

	}

	header = header + ");\n";

	file << header;

	int rowSize = atts.size( );

	for ( unsigned i = 0; i < table.size( ); i++ ) {

		string entry = "INSERT INTO " + relationName + " VALUES FROM (";

		for ( int j = 0; j < rowSize; j++ ) {

			bool flag = (atts.at( j ).t == VARCHAR);

			if ( flag ) {
				entry = entry + '"';
			}

			Entry* thisEntry = table.at( i ).at( j );
			string t;


			if ( thisEntry->isInt( ) ) {
				stringstream ss;
				ss << thisEntry->getEntryI();
				t = ss.str();
			}
			else {
				t = thisEntry->getEntryVC( );
			}

			entry = entry + t;

			if(flag){
				entry = entry + '"';
			}

			if ( j != rowSize - 1 ) {
				entry = entry + ',';
			}

		}

		entry = entry + ");\n";

		file << entry;
	}

	//I'm not sure how this could fail
	return SUCCESS;
}

int Parser::deleteView( string relationName){
	
	vector<Relation>::iterator it;
	
	for( it = views.begin(); it!= views.end(); ++it ) {
		if( it->getName() == relationName ) {
			views.erase( it );
			return SUCCESS;
		}
	}
	
	return INVALID;
}



int Parser::openFile( string relationName ) {

	string line;

	string filename = relationName;

	filename = filename + ".db";

	ifstream file( filename );

	if ( file.is_open( ) ) {

		while ( getline( file, line ) ) {

			parse( line );

		}
		file.close( );
	}
	else {
		//file did not open
		return INVALID;
	}


	return SUCCESS;
}


int Parser::closeFile( string name ) {

	string filename = name + ".db";

	fstream f( name );

	f.close( );

	return SUCCESS;
}


//Gets a relation from views or from database
int Parser::getRelation( string r, Relation& rel ) {

	//check views first
	for ( unsigned i = 0; i < views.size( ); i++ ){
		if ( views.at( i ).getName( ) == r ){
			rel = views.at( i );
			return SUCCESS;
		}
	}

	//if not check database
	if( !database.relationExists( r ) ){
		return INVALID;
	}
	
	rel = database.accessRelation( r );

	return SUCCESS;

}

//DONE
//We pass the integer values of the characters so our check is quick
bool Parser::isAlphaNum( int c ) {

	return ( isAlpha( c ) || isNum( c ) );

}


bool Parser::isAlpha( int c) {

	int A = 65;
	int Z = 90;

	int a = 97;
	int z = 122;

	int UNDERSCORE = 95;

	return ( c >= A && c <= Z ) || ( c >= a && c <= z ) || c == UNDERSCORE;

}


bool Parser::isNum( int c) {

	int ZERO = 48;
	int NINE = 57;

	return (c >= ZERO && c <= NINE );

}

//DONE - NOT TESTED
string Parser::readWord( stringstream& command ) {

	readWhite( command );

	string result = "";
	char next;

	while ( command.peek( ) != '"' ) {

		command.get( next );
		result.push_back( next );

	}

	readWhite( command );

	return result;
}


//DONE - NOT TESTED
string Parser::readAlphaNumWord( stringstream& command ) {

	readWhite( command );

	string result = "";
	char next;

	while ( isAlphaNum( command.peek( ) ) ) {

		command.get( next );
		result.push_back( next );

	}

	readWhite( command );

	return result;
}

//DONE - NOT TESTED
int Parser::readAlphaNumWordStartsAlpha( stringstream& command, string& result ) {

	readWhite( command );

	result = "";
	char next;

	if( !isAlpha( command.peek() ) ){
		return INVALID;
	}
	
	while ( isAlphaNum( command.peek( ) ) ) {

		command.get( next );
		result.push_back( next );

	}

	readWhite( command );

	return SUCCESS;
}


//DONE
void Parser::readWhite( stringstream& command ) {

	while ( command.peek( ) == ' ' ) {
		command.get( );
	}

}


//DONE
int Parser::readSemi( stringstream& command ) {

	readWhite( command );

	char semi;
	command.get( semi );

	if ( semi == ';' ) {
		return SUCCESS;
	}

	command.putback( semi );

	return INVALID;

}


//DONE
int Parser::readArrow( stringstream& command ) {

	readWhite( command );

	char dash;
	char less;

	command.get( less );

	if ( less != '<' || command.peek( ) != '-' ) {

		command.putback( less );
		return INVALID;

	}

	command.get( dash );

	return SUCCESS;

}


//DONE
int Parser::parseAttributeList( stringstream& command, vector<string>& attributeNames ) {

	readWhite( command );

	char open;
	command.get( open );

	if ( open != '(' ) {
		return INVALID;
	}

	char commaOrClose;
	string name;

	do{

		readWhite( command );

		if( readAlphaNumWordStartsAlpha( command, name ) < 0 ){
			return INVALID;
		}
		attributeNames.push_back( name );

		readWhite( command );

		command.get( commaOrClose );

	} while ( commaOrClose == ',' );

	if ( commaOrClose != ')' ){
		return INVALID;
	}

	return SUCCESS;

}


// Parse a typed attribute, does not consume the commas
int Parser::parseTypedAttribute( stringstream& command, vector<Attribute>& attributeList ) {
	// Get attribute name
	string attributeName;
	
	if( readAlphaNumWordStartsAlpha( command, attributeName ) < 0 ){
		return INVALID;
	}

	readWhite( command );

	// Get the type - VARCHAR or INTEGER
	string type = readAlphaNumWord( command );

	if ( type == "VARCHAR" ) {
		// consume the '('
		if ( command.peek( ) != '(' ) {
			return INVALID;
		}
		command.get( );

		// read the size
		int sizeOfString;
		if ( parseInteger( command, sizeOfString ) < 0 ) {
			return INVALID;
		}

		// consume the ')'
		if ( command.peek( ) != ')' ) {
			return INVALID;
		}
		command.get( );

		// not sure what to do with the size here
		Attribute newAttribute( attributeName, VARCHAR, sizeOfString );
		attributeList.push_back( newAttribute );

		return SUCCESS;
	}
	else if ( type == "INTEGER" ) {
		// create the new attribute
		Attribute newAttribute( attributeName, INTEGER );
		attributeList.push_back( newAttribute );

		return SUCCESS;
	}
	else {
		return INVALID;
	}

	readWhite(command);

}


// Parses a create table command and uses the information
// to add the new relation to the database.
int Parser::createTable( stringstream& command ) {
	// Get the relation's name
	string relationName; 
	if( readAlphaNumWordStartsAlpha( command, relationName ) < 0 ){
		return INVALID;
	}

	// Check and consume the opening parenthesis
	char openingParenthesis = command.get( );
	if ( openingParenthesis != '(' ) {
		return INVALID;
	}

	vector<Attribute> attributeList;

	// Parse the attribute list
	while ( command.peek( ) != ')' ) {

		if( parseTypedAttribute( command, attributeList ) < 0 ){
			return INVALID;
		}
		
		// consume the comma if it is there
		if ( command.peek( ) == ',' ) {
			command.get( );
		}

		// get rid of white space if it is there
		readWhite( command );
	}

	// consume closing parenthesis
	char closingParen = command.get( );

	if( closingParen != ')' ){
		return INVALID;
	}

	// Parse the PRIMARY KEY part
	string primaryKeyWord = readAlphaNumWord( command );

	if ( primaryKeyWord != "PRIMARY" ) {
		return INVALID;
	}

	string keyKeyWord = readAlphaNumWord( command );

	if ( keyKeyWord != "KEY" ) {
		return INVALID;
	}

	// Get the key
	vector<string> attributeNames;

	parseAttributeList( command, attributeNames );

	vector<int> keys;

	//Find keys
	for(int i = 0; i < attributeList.size(); i++){

		for(int j = 0; j < attributeNames.size(); j++){

			if( attributeList.at(i).name == attributeNames.at(j) ){
				keys.push_back(i);
				//break inner loop
				j = attributeNames.size();
			}

		}

	}

	database.addRelationToDatabase( relationName, attributeList, keys );

	return SUCCESS;

}


// DONE - not tested
// Parses an update command.
int Parser::update( stringstream& command ) {
	// Get the relation's name
	string relationName;
	if( readAlphaNumWordStartsAlpha( command, relationName ) < 0 ){
		return INVALID;
	}

	Relation targetRelation;
	if( getRelation( relationName, targetRelation) < 0 ){
		return INVALID;
	}

	string setKeyWord = readAlphaNumWord( command );

	if ( setKeyWord != "SET" ) {
		return INVALID;
	}

	vector<string> attributeNames;
	vector<Entry> newValues;

	int index = 0;

	// is this list of stuff suppose to be enclosed in parentheses or not?
	// maybe need a better condition for this loop
	while ( true ) {
		// Parse the attribute name
		string attrName;
		if( readAlphaNumWordStartsAlpha( command, attrName ) < 0 ){
			return INVALID;
		}
		
		// Break if the WHERE key word is reached
		if ( attrName == "WHERE" ) {
			break;
		}
		
		attributeNames.push_back( attrName );
		
		readWhite(command);

		// Check for equal sign
		if ( command.peek( ) != '=' ) {
			return INVALID;
		}
		// Consume equal sign
		command.get( );

		readWhite(command);

		// Parse the literal
		Entry newVal;

		if( targetRelation.getAttributeAt(index).hasSize ){
			newVal.setL(targetRelation.getAttributeAt(index).vcSize); 
		}

		if( readLiteral( command, newVal ) < 0 ){
			return INVALID;
		}

		newValues.push_back( Entry(newVal) );

		// consume a comma if there is one
		if ( command.peek( ) == ',' ) {
			command.get( );
		}

		++index;
	}

	// Get the conditions that will be used by the delete function
	vector<Condition> updateConditions;

	if ( parseConditions( command, updateConditions ) < 0 ) {
		return INVALID;
	}

	//make sure to be updated attributes exist
	for(int i = 0; i < attributeNames.size(); ++i){

		if( !targetRelation.hasAttribute( attributeNames.at(i) ) ){
			return INVALID;
		}

	}

	//check that all condition variables exist in the relation!
	for(int i = 0; i < updateConditions.size(); ++i){

		Condition c = updateConditions.at(i);

		if( c.firstIsVar() ){
			if( !targetRelation.hasAttribute( c.firstVarName() ) ){
				return INVALID;
			}
		}

		if( c.secondIsVar() ){
			if( !targetRelation.hasAttribute( c.secondVarName() ) ){
				return INVALID;
			}
		}

	}

	database.update( relationName, attributeNames, newValues, updateConditions );

	return SUCCESS;
}


// DONE - not tested
// Parses a delete from command.
int Parser::deleteFrom( stringstream& command ) {

	// Get the relation's name
	string relationName;
	
	if( readAlphaNumWordStartsAlpha( command, relationName ) < 0 ){
		return INVALID;
	}

	// Make sure the WHERE keyword is there
	string whereKeyWord = readAlphaNumWord( command );

	if ( whereKeyWord != "WHERE" ) {
		return INVALID;
	}

	// Get the conditions that will be used by the delete function
	vector<Condition> deleteConditions;

	if ( parseConditions( command, deleteConditions ) < 0 ) {
		return INVALID;
	}

	Relation r;
	
	if( getRelation(relationName, r) < 0 ){
		return INVALID;
	}

	//check that all variables exist in the relation!
	for(int i = 0; i < deleteConditions.size(); ++i){

		Condition c = deleteConditions.at(i);

		if( c.firstIsVar() ){
			if( !r.hasAttribute( c.firstVarName() ) ){
				return INVALID;
			}
		}

		if( c.secondIsVar() ){
			if( !r.hasAttribute( c.secondVarName() ) ){
				return INVALID;
			}
		}

	}


	// Call the delete function on the relation
	database.deleteFromRelation( relationName, deleteConditions );

	return SUCCESS;
}


// Reads a literal into the passed in Entry object.
int Parser::readLiteral( stringstream& command, Entry& e ) {

	readWhite(command);

	int a;

	// Check for an int, if so then create the literal with that int
	// otherwise parse a string
	if ( parseInteger( command, a ) < 0 ){

		char quote;
		command.get(quote);

		if(quote != '"'){
			return INVALID;
		}

		e.setVC( readWord( command ) );

		command.get(quote);
		if(quote != '"'){
			return INVALID;
		}

	}
	else {

		e.setInt( a );

	}

	return SUCCESS;
}


// Done, for sure needs testing -------should this check that the tuple has the right attributes for the relation or should database check?
int Parser::insertInto( stringstream& command ) {

	// Get the target Relation name
	string relationName; 
	if( readAlphaNumWordStartsAlpha( command, relationName ) < 0 ){
		return INVALID;
	}

	Relation targetRelation;
	if( getRelation( relationName, targetRelation ) < 0 ){
		return INVALID;
	}

	// Read and verify the VALUES key word.
	string valuesKeyWord = readAlphaNumWord( command );
	if ( valuesKeyWord != "VALUES" ) {
		return INVALID;
	}

	// Read and verify the FROM key word.
	string fromKeyWord = readAlphaNumWord( command );
	if ( fromKeyWord != "FROM" ) {
		return INVALID;
	}

	readWhite( command );

	// Check for the opening parenthesis
	char parenthesis = command.peek( );

	if ( parenthesis == '(' ) {
		command.get( );

		vector<Entry> tuple;
		Entry helperEntry;
		
		
		
		int index = 0;
		// keep reading literals until there is a ')'
		while ( command.peek( ) != ')' ) {

			Entry helperEntry;

			if( targetRelation.getAttributeAt(index).hasSize ){
				helperEntry.setL( targetRelation.getAttributeAt(index).vcSize );
			}


			if( readLiteral( command, helperEntry ) < 0 ){
				return INVALID;
			}

			tuple.push_back( Entry( helperEntry ) );

			readWhite(command);

			char next = command.peek();
			// consume the comma if there is one
			if ( next == ',' ) {
				command.get( );
			}else if( next != ')' ){
				return INVALID;
			}

			++index;
		}

		// consume the closing parenthesis
		char close;
		command.get( close );

		if( targetRelation.hasTuple( tuple ) ){
			return INVALID;
		}

		database.addTupleToRelation( tuple, database.accessRelationPointer( relationName ) );
	}
	// If there is no opening parenthesis then it must be dealing with a relation
	else {

		// Read and verify the relation key word
		string relationKeyWord = readAlphaNumWord( command );
		if ( relationKeyWord != "RELATION" ) {
			return INVALID;
		}

		// Get the target relation
		Relation whatToReadFrom;
		if( parseExpr( command, whatToReadFrom ) < 0 ){
			return INVALID;
		}

		database.insertIntoFromRelation( database.accessRelationPointer( relationName ), whatToReadFrom );
	}

	return SUCCESS;
}



//DONE
int Parser::projection( stringstream& command, Relation& rel ) {

	vector<string> attributeNames;

	if ( parseAttributeList( command, attributeNames ) < 0 ) {
		return INVALID;
	}

	Relation r; 
	if( parseExpr( command, r ) < 0 ){
		return INVALID;
	}

	for(int i = 0; i < attributeNames.size(); ++i){

		if( !r.hasAttribute( attributeNames.at(i) ) ){
			return INVALID;
		}

	}

	rel = database.projection( attributeNames, r );
	return SUCCESS;

}

//DONE
int Parser::rename( stringstream& command, Relation& rel ) {

	readWhite( command );

	vector<string> attributeNames;

	if ( parseAttributeList( command, attributeNames ) < 0 ) {
		return INVALID;
	}

	Relation r; 
	if( parseExpr( command, r ) < 0 ){
		return INVALID;
	}
	
	rel = database.renameAttributes( attributeNames, r );

	return SUCCESS;

}

//DONE - NOT TESTED
int Parser::parseCommand( stringstream& command ){

	string word = readAlphaNumWord( command );

	if ( word == "OPEN" ) {

		string relationName; 
		if( readAlphaNumWordStartsAlpha( command, relationName ) < 0 ){
			return INVALID;
		}

		//Catch problem before execution
		if ( readSemi( command ) < 0 ) {
			return INVALID;
		}

		openFile( relationName );

		return SUCCESS;

	}
	else if ( word == "CLOSE" ) {

		string relationName;
		if( readAlphaNumWordStartsAlpha( command, relationName ) < 0 ){
			return INVALID;
		}

		if ( closeFile( relationName ) < 0 ) {
			return INVALID;
		}

		if ( readSemi( command ) < 0 ) {
			return INVALID;
		}

		return SUCCESS;

	}
	else if ( word == "SHOW" ) {

		string relationName; 
		if( readAlphaNumWordStartsAlpha( command, relationName ) < 0 ){
			return INVALID;
		}

		//Catch problem before execution
		if ( readSemi( command ) < 0 ) {
			return INVALID;
		}

		Relation r; 
		if( getRelation( relationName, r ) < 0 ){
			return INVALID;
		}


		cout << r;

		return SUCCESS;

	}
	else if ( word == "WRITE" ) {

		string relationName; 
		if( readAlphaNumWordStartsAlpha( command, relationName ) < 0 ){
			return INVALID;
		}

		//Catch problem before execution
		if ( readSemi( command ) < 0 ) {
			return INVALID;
		}

		if ( writeFile( relationName ) < 0 ) {
			return INVALID;
		}

		return SUCCESS;

	}
	else if ( word == "INSERT" ) {

		string into = readAlphaNumWord( command );

		if ( into != "INTO" ) {
			return INVALID;
		}

		if ( insertInto( command ) < 0 ) {
			return INVALID;
		}

		return SUCCESS;

	}
	else if ( word == "DELETE" ) {

		string from = readAlphaNumWord( command );

		if ( from != "FROM" ) {
			return INVALID;
		}

		if ( deleteFrom( command ) < 0 ) {
			return INVALID;
		}

		return SUCCESS;

	}
	else if ( word == "CREATE" ) {
		string table = readAlphaNumWord( command );

		if ( table != "TABLE" ) {
			return INVALID;
		}

		if ( createTable( command ) < 0 ) {
			return INVALID;
		}

		return SUCCESS;

	}
	else if ( word == "UPDATE" ) {

		if ( update( command ) < 0 ) {
			return INVALID;
		}

		return SUCCESS;

	}
	
	else if ( word == "DROP" ) {
		string table = readAlphaNumWord( command );

		if ( table != "TABLE" ) {
			return INVALID;
		}
		string relationName;
		if( readAlphaNumWordStartsAlpha( command, relationName ) < 0 ){
			return INVALID;
		}

		deleteView( relationName );
		//need to delete from view not database


		return SUCCESS;
	}
	else {

		return INVALID;

	}

}

//DONE - NOT DEBUGGED
int Parser::parseQuery( stringstream& command ){

	string relationName; 
	if( readAlphaNumWordStartsAlpha( command, relationName ) < 0 ){
		return INVALID;
	}

	if ( readArrow( command ) < 0 ){
		return INVALID;
	}

	Relation targetRelation; 
	if( parseExpr( command, targetRelation ) < 0 ){
		return INVALID;
	}

	readWhite(command);

	if( readSemi( command ) < 0 ){
		return INVALID;
	}

	result = database.getResultMatrix();

	readWhite(command);

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

	if ( sub != '-' ){ 
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
		else {
			o = EQUALS;
			return SUCCESS;
		}
		break;

	case ( '!' ) :

		command.get( c );
		if ( c != '=' ){
			return INVALID;
		}
		else {
			o = NEQ;
			return SUCCESS;
		}
		break;

	case ( '<' ) :

		c = command.peek( );

		if ( c != '=' ){
			o = LE;
		}
		else {
			o = LEQ;
		}
		return SUCCESS;
		break;

	case ( '>' ) :

		c = command.peek( );

		if ( c != '=' ){
			o = GR;
		}
		else {
			o = GREQ;
		}
		return SUCCESS;
		break;

	default:
		return INVALID;


	}

	return INVALID;

}

//TODO
//Put an integer from command into 'i'. Return invalid if method fails
//IF THE METHOD FAILS THIS FUNCTION MUST RETURN COMMAND TO ITS INITIAL STATE
int Parser::parseInteger( stringstream& command, int& arg ) {

	vector<char> chars;

	//push back until we find something not an int
	while ( isNum( command.peek( ) ) ){
		chars.push_back( command.get( ) );
	}

	if ( isAlpha( command.peek( ) ) || chars.size() == 0 ){

		for ( int i = chars.size( ) - 1; i >= 0; i-- ){

			command.putback( chars.at( i ) );

		}

		return INVALID;
	}
	else {

		string a = "";
		for ( unsigned i = 0; i < chars.size( ); i++ ){
			a.push_back( chars.at( i ) );
		}

		stringstream ss;
		ss << a;
		ss >> arg;

		return SUCCESS;
	}



}


int Parser::findConnector( stringstream& command, Connector& c, int paren ){
	//char count
	int cc = 0;
	readWhite( command );

	char next;

	command.get( next );
	++cc;
	while ( next == ')' || next == ' ' ){
		//if it was a parentheses, keep track to see if we hit the end of the condition list
		if ( next == ')' ){
			paren--;

			if ( paren == 0 ){
				c = NONE;
				for(int i = 0; i < cc; ++i){
					command.unget();
				}
				return SUCCESS;
			}

		}

		command.get( next );
		++cc;
	}

	if ( next == '&' ){
		command.get( next );
		++cc;
		if ( next == '&' ){

			c = AND;
			for(int i = 0; i < cc; ++i){
				command.unget();
			}
			return SUCCESS;

		} else {
			return INVALID;
		}

	}
	else if ( next == '|' ){

		command.get( next );
		++cc;
		if ( next == '|' ){
			c = OR;
			for(int i = 0; i < cc; ++i){
				command.unget();
			}
			return SUCCESS;
		} else {
			return INVALID;
		}

	}
	else {
		return INVALID;
	}

}

//DONE
int Parser::parseCondition( stringstream& localCommand, int paren, Condition& condition ) {

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
	else {

		//If not, it could either be a literal integer, or it is an attribute

		if ( parseInteger( localCommand, firstI ) < 0 ){
			//parseInteger FAILED - it is attribute

			if( readAlphaNumWordStartsAlpha( localCommand, first ) < 0 ){
				return INVALID;
			}
		} else {
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
		return INVALID;
	}

	readWhite( localCommand );

	next = localCommand.peek( );

		//Check if the string starts with a quote. If it does it is a literal string
	if ( next == '"' ){
		secondIsLit = true;
		secondIsStr = true;
		localCommand.get( );
		second = readAlphaNumWord( localCommand );
		b.setVC(second);
	}
	else {

		//If not, it could either be a literal integer, or it is an attribute

		if ( parseInteger( localCommand, secondI ) < 0 ){
			//parseInteger FAILED - it is attribute

			if( readAlphaNumWordStartsAlpha( localCommand, second ) < 0 ){
				return INVALID;
			}
		} else {
			//parseInteger SUCCESS - it is int

			secondIsLit = true;
			b.setInt(secondI);
		}

	}

	if ( secondIsStr ){

		localCommand.get( next );

		if ( next != '"' ){
			return INVALID;
		}

	}

	Connector conn = NONE;


	if( findConnector(localCommand, conn, paren) < 0 ){
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

string Parser::myGetLine( stringstream& command ){

	string result = "";
	char next;
	

	while( command.get(next) ){
		result.push_back(next);
	}

	return result;

}


int Parser::parseConditions( stringstream& command, vector<Condition>& conditions ) {

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

		//Read in a (Open Parentheses) OR (name OR string) Operator (name OR string) (Optional Parens) Connector

		Condition c;

		readWhite( command );

		next = command.peek();

		if ( next == '(' ){
			++paren;
		}
		else{

			if( parseCondition(command, paren, c) < 0 ){
				return INVALID;
			}

			conditions.push_back(Condition(c));
		}

		readWhite(command);

		char closeParen = command.peek();

		while(closeParen == ')'){
			command.get();
			paren--;
			readWhite(command);
			closeParen = command.peek();

			if( paren == 0 ){
				break;
			}
		}


		//This parses a strange way - the condition parser has already looked ahead to see
		//if theres a connector, but we still need to get rid of it if there was
		char connector = command.peek();

		switch (connector){

		case ('&'):
			command.get();
			if( command.get() != '&' ){
				return INVALID;
			}
			break;

		case ('|'):
			command.get();
			if( command.get() != '|' ){
				return INVALID;
			}
			break;
		}

	}

	//if paren == 0, we're done

	return SUCCESS;
}

//DONE - NOT DEBUGGED
int Parser::parseExpr( stringstream& command, Relation& rel ){

	readWhite( command );

	//Parentheses are optional. We ask here, did they put them in?
	bool openParen = false;

	if ( command.peek( ) == '(' ){
		openParen = true;
		command.get( );
	}

	//Find command it matches to.

	//Could be word, or relation name, or relation name followed by +/-

	string word = readAlphaNumWord( command );

	Relation targetRelation;

	if ( word == "project" ){

		if( projection( command, targetRelation ) < 0 ){
			return INVALID;
		}

		readWhite( command );

		if ( openParen && command.peek( ) != ')' ){
			return INVALID;
		}else if( openParen ){
			command.get( );
		}

		

		rel = targetRelation;
		
		return SUCCESS;

	}
	else if ( word == "select" ){

		if( selection( command, targetRelation ) < 0 ){
			return INVALID;
		}

		readWhite( command );

		if ( openParen && command.peek( ) != ')' ){
			return INVALID;
		}else if( openParen ){
			command.get( );
		}

		rel = targetRelation;
		
		return SUCCESS;

	}
	else if ( word == "rename" ){

		if( rename( command, targetRelation ) < 0 ){
			return INVALID;
		}

		readWhite( command );

		if ( openParen && command.peek( ) != ')' ){
			return INVALID;
		}else if( openParen ){
			command.get( );
		}

		

		rel = targetRelation;
		
		return SUCCESS;

	}
	else{

		//At this point we assume what we have is the name of a relation

		string relationA = word;


		if ( peekAndReadAddition( command ) > 0 ){

			Relation relationB; 
			if( parseExpr( command, relationB ) < 0 ){
				return INVALID;
			}

			Relation targetRelationA; 
			
			if( getRelation( relationA, targetRelationA ) < 0 ){
				return INVALID;
			}


			targetRelation = database.unionTwoRelations( targetRelationA, &relationB );

			readWhite( command );

			if ( openParen && command.peek( ) != ')' ){
				return INVALID;
			}else if( openParen ){
				command.get( );
			}

			

			rel = targetRelation;
			
			return SUCCESS;

		}
		else if ( peekAndReadSubtraction( command ) > 0 ){

			Relation relationB; 
			if( parseExpr( command, relationB ) < 0 ){
				return INVALID;
			}


			Relation targetRelationA;
			if( getRelation( relationA, targetRelationA ) < 0 ){
				return INVALID;
			}

			targetRelation = database.differenceTwoRelation( targetRelationA , relationB );

			readWhite( command );

			if ( openParen && command.peek( ) != ')' ){
				return INVALID;
			}else if( openParen ){
				command.get( );
			}

			

			rel = targetRelation;
			
			return SUCCESS;

		}
		else if ( peekAndReadMultiplication( command ) > 0 ){

			Relation relationB;
			if( parseExpr( command, relationB ) < 0 ){
				return INVALID;
			}

			Relation targetRelationA;
			if( getRelation( relationA, targetRelationA ) < 0 ){
				return INVALID;
			}

			targetRelation = database.crossProduct( targetRelationA , relationB );

			readWhite( command );

			if ( openParen && command.peek( ) != ')' ){
				return INVALID;
			}else if( openParen ){
				command.get( );
			}

			

			rel = targetRelation;
			
			return SUCCESS;

		}
		else{

			//Only valid operation left is JOIN or a relation name

			string join = readAlphaNumWord( command );

			if ( join != "JOIN" ){
				
				Relation targetRelationA;
				if( getRelation( relationA, targetRelationA ) < 0 ){
					return INVALID;
				}

				rel = targetRelationA;

				return SUCCESS;

			}

			string relationB = readAlphaNumWord( command );

			targetRelation = database.naturalJoin( relationA, relationB );

			readWhite( command );

			if ( openParen && command.peek( ) != ')' ){
				return INVALID;
			}else if( openParen ){
				command.get( );
			}

			rel = targetRelation;
			
			return SUCCESS;

		}


	}


}

int Parser::parse( string s ){

	

	if ( s == "EXIT;" || s == "EXIT; " ){
		return EXIT;
	}

	stringstream command;
	command << s;

	//Try to parse it as a command - if it returns error, then we continue
	if ( parseCommand( command ) > 0 ){

		return SUCCESS;

	}

	//Get a new stream
	stringstream second;
	second << s;

	if ( parseQuery( second ) > 0 ){
		return SUCCESS;
	}

	return INVALID;
}


// DONE - not tested
int Parser::selection( stringstream& command, Relation& rel ) {

	// Parse and get the conditions
	vector<Condition> conditions;

	// If no conditions then return empty Relation
	if ( parseConditions( command, conditions ) < 0 ) {
		return INVALID;
	}

	// Get the target relation
	Relation targetRelation;
	if( parseExpr( command, targetRelation ) < 0 ){
		return INVALID;
	}

	//check that all variables exist in the relation!
	for(int i = 0; i < conditions.size(); ++i){

		Condition c = conditions.at(i);

		if( c.firstIsVar() ){
			if( !targetRelation.hasAttribute( c.firstVarName() ) ){
				return INVALID;
			}
		}

		if( c.secondIsVar() ){
			if( !targetRelation.hasAttribute( c.secondVarName() ) ){
				return INVALID;
			}
		}

	}

	rel = database.selection( conditions, targetRelation );
	// return the result of the selection operation
	return SUCCESS;


}
