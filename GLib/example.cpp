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

/* GLib function objects */
GLuaFunction *addNumbers;
GLuaFunction *factorial;
GLuaFunction *dot;

// The GLib plugin object
GLuaPlugin *plugin;

/* Some functions that we will register later */

// Simple function that adds two numbers
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

// Simple function that calculates a factorial
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

// More complex function that calculates the dot product of two vectors
int f_dot(lua_State* state) {
	std::vector<GLuaObject> params = dot->GetParams(state);

	Vector a = params[0].vector_value;
	Vector b = params[1].vector_value;

	double sum = 0;

	sum += a.x * b.x;
	sum += a.y * b.y;
	sum += a.z * b.z;

	ReturnNumber(sum);
}

/* -------- */

GMOD_MODULE_OPEN() {

	// Create plugin "plugin name", "plugin version", "plugin table name"
	// If functions are not registered using RegisterGlobal(), they will be stored in the plugin table.
	// This helps to avoid conflicting function names, and keeps things tidy.
	plugin = new GLuaPlugin("ExamplePlugin", "1.0.0", "EPlugin", LUA);

	// Add function, defining the parameter types we expect, and passing a function pointer
	addNumbers = new GLuaFunction("addNumbers", std::vector<char> {GLua::NUMBER, GLua::NUMBER}, f_addNumbers);
	factorial = new GLuaFunction("factorial", std::vector<char> {GLua::NUMBER}, f_factorial);
	dot = new GLuaFunction("dot", std::vector<char> {GLua::VECTOR, GLua::VECTOR}, f_dot);

	// Cache functions with the plugin to be registered on startup.
	plugin->Register(*addNumbers);
	plugin->Register(*factorial);
	plugin->Register(*dot);
	
	// Start plugin and perform setup
	plugin->Start();

	return 0;
}

GMOD_MODULE_CLOSE() {
	return 0;
}