/*
	This file defines the available types to be acessible within a GLua function.

	Author: Techmo
	Last modified: 4 July 2019
*/
#include "GIncludes.h"

#ifndef LUA_TYPE_h
#define LUA_TYPE_h

namespace GLua {

	enum : char {
		BOOL,
		NUMBER,
		STRING,
		VECTOR,
		ANGLE
	};

}

#endif //LUA_TYPE_h
