#include "GLuaFunction.h"
#include "GLuaUtil.h"

inline int ReturnMulti(std::vector<GLuaObject> values, lua_State* state) {
	int count = 0;
	for (GLuaObject value : values) {
		switch (value.type) {
		case GLua::BOOL:
			state->luabase->PushBool(value.boolean_value);
			count++;
			break;
		case GLua::NUMBER:
			state->luabase->PushNumber(value.number_value);
			count++;
			break;
		case GLua::STRING:
			state->luabase->PushString(value.string_value);
			count++;
			break;
		case GLua::VECTOR:
			state->luabase->PushVector(value.vector_value);
			count++;
			break;
		case GLua::ANGLE:
			state->luabase->PushAngle(value.angle_value);
			count++;
			break;
		default:
			printf("GLua: ERROR: Attempt to return unsupported datatype %d\n", value.type);
			break;
		}
	}

	return count;
}

GLuaFunction::GLuaFunction(const char* _name, std::vector<char> _param_types, int(*_execute)(lua_State* state)) {
	name = _name;
	param_types = _param_types;
	execute = _execute;
}

GLuaFunction::~GLuaFunction() {

}

std::vector<GLuaObject> GLuaFunction::GetParams(lua_State* state) {

	int stack_idx = 1;
	std::vector<GLuaObject> params;
	GLuaObject o;

	state->luabase->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

	for (char ptype : param_types) {
		switch (ptype) {
		case GLua::NUMBER:
			state->luabase->CheckType(stack_idx, GarrysMod::Lua::Type::NUMBER);
			o.type = GLua::NUMBER;
			o.number_value = state->luabase->GetNumber(stack_idx);
			params.push_back(o);
			break;
		case GLua::BOOL:
			state->luabase->CheckType(stack_idx, GarrysMod::Lua::Type::BOOL);
			o.type = GLua::BOOL;
			o.boolean_value = state->luabase->GetBool(stack_idx);
			params.push_back(o);
			break;
		case GLua::STRING:
			state->luabase->CheckType(stack_idx, GarrysMod::Lua::Type::STRING);
			o.type = GLua::STRING;
			o.string_value = (char*) state->luabase->GetString(stack_idx);
			params.push_back(o);
			break;
		case GLua::VECTOR:
			o.type = GLua::VECTOR;
			o.vector_value = state->luabase->GetVector(stack_idx);
			params.push_back(o);
			break;
		case GLua::ANGLE:
			o.type = GLua::ANGLE;
			o.angle_value = state->luabase->GetAngle(stack_idx);
			params.push_back(o);
			break;
		default:
			printf("GLib: ERROR: Invalid param type encountered while processing params for function %s\n", name);
		}
		stack_idx++;
	}

	state->luabase->Pop();

	return params;
}

