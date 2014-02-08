#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include "Type.h"

struct Attribute{

	Type t;
	string name;

	Attribute(string n, Type ty) : t(ty), name(n) {}

};

#endif