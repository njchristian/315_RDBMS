#ifndef PARSER_H_
#define PARSER_H_

#include "Database.h"

class Parser{

	Database& database;


public:

	Parser(Database& d) : database(d) {}

};

#endif