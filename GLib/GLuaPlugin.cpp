#include "GLuaPlugin.h"
#include <sstream>

GLuaPlugin::GLuaPlugin(const char* _name, const char* _version, const char* _tname, lua_State* _state){
	state = _state;
	name = _name;
	version = _version;
	tname = _tname;
}

GLuaPlugin::~GLuaPlugin() {

}

void GLuaPlugin::Start() {

	/*
	// Get interface to server binaries
	engine_loader = new SourceSDK::FactoryLoader(engine_lib, false, false);
	server_loader = new SourceSDK::FactoryLoader(server_lib, false, false);

	engine = engine_loader->GetInterface<IVEngineServer>(INTERFACEVERSION_VENGINESERVER);
	if (engine == nullptr)
		LUA->ThrowError("GLib: ERR: Failed to retrieve server engine interface.");

	IServer **pserver = nullptr;
	{
		SymbolFinder symfinder;

		pserver = reinterpret_cast<IServer **>(symfinder.ResolveOnBinary(
			engine_lib.c_str(), IServer_sig, IServer_siglen
		));
	}

	if (pserver == nullptr)
		LUA->ThrowError("GLib: ERR: Failed to locate IServer pointer.");

	server = *pserver;
	if (server == nullptr)
		LUA->ThrowError("GLib: ERR: failed to locate IServer.");

	enginetrace = engine_loader->GetInterface<IEngineTrace>(INTERFACEVERSION_ENGINETRACE_SERVER);
	if (engine == nullptr)
		LUA->ThrowError("GLib: ERR: Failed to retrieve server engine trace interface.");

		*/
	// Register global plugins
	
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

	for (GLuaFunction* func : r_global_functions) {
		LUA->PushCFunction(func->execute);
		LUA->SetField(-2, func->name);
	}

	LUA->Pop();

	// Register local functions
	LUA->CreateTable();
	LUA->PushString(version);
	LUA->SetField(-2, "Version");

	LUA->PushNumber(0);
	LUA->SetField(-2, "VersionNum");

	for (GLuaFunction* func : r_functions) {
		LUA->PushCFunction(func->execute);
		LUA->SetField(-2, func->name);
	}

	LUA->SetField(GarrysMod::Lua::INDEX_GLOBAL, tname);
}

void GLuaPlugin::Register(GLuaFunction* _func) {
	r_functions.push_back(_func);
	r_functions[r_functions.size() - 1]->SetState(state);
}

void GLuaPlugin::RegisterGlobal(GLuaFunction* _func) {
	r_global_functions.push_back(_func);
	r_global_functions[r_global_functions.size() - 1]->SetState(state);
}

void GLuaPlugin::ThrowErrorSoft(const char* error) {
	GarrysMod::Lua::ILuaInterface* interface = reinterpret_cast<GarrysMod::Lua::ILuaInterface*> (state->luabase);

	interface->ErrorNoHalt("ERR: %s:, %s\n", name, error);
}

void GLuaPlugin::ThrowErrorHard(const char* error) {
	GarrysMod::Lua::ILuaInterface* interface = reinterpret_cast<GarrysMod::Lua::ILuaInterface*> (state->luabase);
	std::ostringstream strstream;

	strstream << "ERR: ";
	strstream << name;
	strstream << ": ";
	strstream << error;
	strstream << std::endl;

	interface->ThrowError(strstream.str().c_str());
}

GarrysMod::Lua::ILuaInterface* GLuaPlugin::GetLuaInterface() {
	return reinterpret_cast<GarrysMod::Lua::ILuaInterface*> (state->luabase);
}
