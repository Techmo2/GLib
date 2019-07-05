/*
	GLib Example Plugin

	A Test script is provided in the project folder.

	Author: Techmo
	Last Modified: 4 July 2019
*/

#include "GLuaFunction.h"
#include "GLuaObject.h"
#include "GLuaPlugin.h"
#include "GLuaUtil.h"

#define GMOD_MODULE

GLuaFunction *addNumbers;
GLuaFunction *factorial;
GLuaPlugin *plugin;

int f_addNumbers(lua_State* state) {

	// Retrieve function parameters
	std::vector<GLuaObject> params = addNumbers->GetParams(state);

	// Get parameter values
	double a = params[0].number_value;
	double b = params[1].number_value;

	// Calculate sum
	double sum = a + b;

	// Return sum
	ReturnNumber(sum);
}

int f_factorial(lua_State* state) {

	// Retrieve function parameters
	std::vector<GLuaObject> params = factorial->GetParams(state);

	// Get factorial base
	int n = (int) params[0].number_value;

	// Calculate factorial
	double fact = 1;

	for (int i = 1; i < n; ++i) {
		fact *= i;
	}

	// Return factorial
	ReturnNumber(fact);
}

GMOD_MODULE_OPEN() {
	// Create plugin "plugin name", "plugin version", "local function table name"
	plugin = new GLuaPlugin("ExamplePlugin", "1.0.0", "EPlugin", LUA);

	// Add function, defining the parameter types we expect, and passing a function pointer
	addNumbers = new GLuaFunction("addNumbers", std::vector<char> {GLua::NUMBER, GLua::NUMBER}, f_addNumbers);
	factorial = new GLuaFunction("factorial", std::vector<char> {GLua::NUMBER}, f_factorial);

	// Register function
	plugin->Register(*addNumbers);
	plugin->Register(*factorial);
	
	// Start plugin, perform setup
	plugin->Start();

	return 0;
}

GMOD_MODULE_CLOSE() {
	return 0;
}