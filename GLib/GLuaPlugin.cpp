#include "GLuaPlugin.h"

GLuaPlugin::GLuaPlugin(const char* _name, const char* _version, const char* _tname, GarrysMod::Lua::ILuaBase* _state){
	state = _state;
	name = _name;
	version = _version;
	tname = _tname;
}

GLuaPlugin::~GLuaPlugin() {

}

void GLuaPlugin::Start() {
	// Register global plugins
	
	state->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

	for (GLuaFunction func : r_global_functions) {
		state->PushCFunction(func.execute);
		state->SetField(-2, func.name);
	}

	state->Pop();

	// Register local functions
	state->CreateTable();
	state->PushString(version);
	state->SetField(-2, "Version");

	state->PushNumber(0);
	state->SetField(-2, "VersionNum");

	for (GLuaFunction func : r_functions) {
		state->PushCFunction(func.execute);
		state->SetField(-2, func.name);
	}

	state->SetField(GarrysMod::Lua::INDEX_GLOBAL, tname);
}

void GLuaPlugin::Register(GLuaFunction _func) {
	r_functions.push_back(_func);
}

void GLuaPlugin::RegisterGlobal(GLuaFunction _func) {
	r_global_functions.push_back(_func);
}
