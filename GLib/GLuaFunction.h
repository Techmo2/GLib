/*
	This class defines a c function to be registered with the game, and 
	a few utilities to make the implementation easier and cleaner.
	The function parameters are predefined by a provided vector.

	Author: Techmo
	Last modified: 8 July 2019
*/

#ifndef LUA_FUNCTION_h
#define LUA_FUNCTION_h

#include "GIncludes.h"
#include <GarrysMod/Lua/Interface.h>
#include <GarrysMod/Lua/LuaObject.h>
#include <vector>

/* Return a number */
#define ReturnNumber(value) \
	state->luabase->PushNumber(value); \
	return 1

/* Return a boolean */
#define ReturnBool(value) \
	state->luabase->PushBool(value); \
	return 1

/* Return a string */
#define ReturnString(value) \
	state->luabase->PushString(value); \
	return 1

/* Return a vector */
#define ReturnVector(value) \
	state->luabase->PushVector(value); \
	return 1

/* Return an angle */
#define ReturnAngle(value) \
	state->luabase->PushAngle(value); \
	return 1

/*
/// <summary> Allows for the return of multiple values from a c function. </summary>
///
/// <param name="values"> An vector of type GLuaObject containing values to be returned. </param>
/// <param name="state"> A pointer to the current lua state. </param>
inline int ReturnMulti(std::vector<GarrysMod::Lua::ILuaObject*> values, lua_State* state);
*/


class GLuaFunction {
private:
	lua_State* state;
public:
	const char* name;
	int(*execute)(lua_State* state);
	std::vector<int> pfilter;
	/// <summary>
	/// Creates a new GLua function with the specified name and parameter types. Calls the provided
	/// function pointer on execution.
	/// </summary>
	///
	/// <param name="_name"> The name of the function to be used within lua. </param>
	/// <param name="_execute"> A c function to be called when the function is called within lua. </param>
	/// <param name="_state"> A pointer to the lua state. </param>
	GLuaFunction(const char* _name, int(*_execute)(lua_State* state));

	~GLuaFunction();

	/// <summary>
	/// Automatically retrieves parameters passed to the c function and packs them into a vector.
	/// </summary>
	///
	/// <returns> A vector of type GLuaObject containing the parameters passed to the c function from lua. </returns>
	std::vector<GarrysMod::Lua::ILuaObject*> GetParams();

	/// <summary>
	/// Enable automatic parameter type checking, and set the type filter to the provided vector
	/// </summary>
	///
	/// <param name="filter"> A vector of type GarrysMod::Lua::Type to be used as a filter. </param>
	void SetParamFilter(std::vector<int> filter);

	/// <summary>
	/// A simple utility function that clears the lua stack.
	/// </summary>
	void ClearStack();

	/// <summary>
	/// Sets the lua state pointer for the function to use. Automatically done by the plugin class on start.
	/// </summary>
	void SetState(lua_State* _state);
};

#endif //LUA_FUNCTION_h
