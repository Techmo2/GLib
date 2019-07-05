#include "GLuaObject.h"

GLuaObject::GLuaObject() {}

GLuaObject::GLuaObject(bool value) {
	type = GarrysMod::Lua::Type::BOOL;
	boolean_value = value;
}

GLuaObject::GLuaObject(double value) {
	type = GLua::NUMBER;
	number_value = value;
}

GLuaObject::GLuaObject(char* value) {
	type = GLua::STRING;
	string_value = value;
}

GLuaObject::GLuaObject(Vector value) {
	type = GLua::VECTOR;
	vector_value = value;
}

/*
GLuaObject::GLuaObject(Color value) {
	type = GLua::COLOR;
	color_value = value;
}
*/

GLuaObject::GLuaObject(QAngle value) {
	type = GLua::ANGLE;
	angle_value = value;
}

GLuaObject::~GLuaObject() {

}