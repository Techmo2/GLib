/*
	This is the plugin class. This class handles the various defined functions and registers
	them with the game when the plugin starts up.

	Author: Techmo
	Last modified: 4 July 2019
*/

#ifndef LUA_PLUGIN_h
#define LUA_PLUGIN_h

#include "GLuaFunction.h"

class GLuaPlugin {
private:
	const char* version;
	const char* name;
	const char* tname;
	GarrysMod::Lua::ILuaBase* state;
	std::vector<GLuaFunction> r_functions;
	std::vector<GLuaFunction> r_global_functions;
public:

	/// <summary>
	/// Creates a new GLua plugin object.
	/// </summary>
	///
	/// <param name="_name"> The name of the plugin. </param>
	/// <param name="_version"> The version of the plugin. </param>
	/// <param name="_tname"> The name of the table in which to register non global functions. Keeps lua code tidy. </param>
	/// <param name="_state"> A pointer to the lua state. </param>
	GLuaPlugin(const char* _name, const char* _version, const char* _tname, GarrysMod::Lua::ILuaBase* _state);
	~GLuaPlugin();

	/// <summary>
	/// Registers all cached functions with the game and initializes the plugin.
	/// </summary>
	void Start();

	/// <summary>
	/// Caches a GLuaFunction to be registered in the plugin table when the plugin starts.
	/// </summary>
	///
	/// <param name="_func"> The GLuaFunction to be registered. </param>
	void Register(GLuaFunction _func);

	/// <summary>
	/// Caches a GLuaFunction to be registered in the global table when the plugin starts.
	/// </summary>
	///
	/// <param name="_func"> The GLuaFunction to be registered. </param>
	void RegisterGlobal(GLuaFunction _func);
};

#endif //LUA_PLUGIN_h
