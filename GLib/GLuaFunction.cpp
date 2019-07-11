#include "GLuaFunction.h"
#include "GLuaUtil.h"

/*
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
*/

GLuaFunction::GLuaFunction(const char* _name, int(*_execute)(lua_State* state), lua_State* _state) {
	name = _name;
	execute = _execute;
	state = _state;
}

GLuaFunction::~GLuaFunction() {

}

std::vector<GarrysMod::Lua::ILuaObject*> GLuaFunction::GetParams() {
	GarrysMod::Lua::ILuaInterface *interface = reinterpret_cast<GarrysMod::Lua::ILuaInterface*>(state->luabase);

	int num_params = interface->Top();

	std::vector<GarrysMod::Lua::ILuaObject*> params;

	// Check parameter types if enabled
	if (pfilter.size() > 0) {
		int idx = 1;
		for (int t : pfilter) {
			if (idx > num_params) {
				printf("GLib: ERR: Numper of filter types defined exceeds number of parameters passed. Skipping parameter check for function %s.\n", name);
				break;
			}
			interface->CheckType(idx, t);
		}
	}

	// Get parameter lua objects
	interface->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

	for (int stack_idx = 1; stack_idx <= num_params; stack_idx++) {
		GarrysMod::Lua::ILuaObject* o;
		o = interface->GetObject(stack_idx);
		params.push_back(o);
	}

	interface->Pop();

	return params;
}

void GLuaFunction::SetParamFilter(std::vector<int> filter) {
	pfilter = filter;
}

void GLuaFunction::ClearStack() {
	int stack_size = state->luabase->Top();
	state->luabase->Pop(stack_size);
}


