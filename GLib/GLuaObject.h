/*
	This class holds various possible data values that are passed
	to and from lua, and makes them easily acessible within c.

	Author: Techmo
	Last modified: 4 July 2019
*/

#ifndef LUA_OBJECT_h
#define LUA_OBJECT_h

#include <GarrysMod/Lua/AutoReference.h>
#include "GLuaType.h"

class GLuaObject {
public:
	int type;

	union {
		bool boolean_value;
		double number_value;
		char* string_value;
		Vector vector_value;
		//Color color_value;
		QAngle angle_value;
	};

	GLuaObject();
	GLuaObject(bool value);
	GLuaObject(double value);
	GLuaObject(char* value);
	GLuaObject(Vector value);
	//GLuaObject(Color value);
	GLuaObject(QAngle value);

	~GLuaObject();
};

#endif //LUA_OBJECT_h
