/*
	This file defines a number of helpful tools and utilities.

	Author: Techmo
	Last modified: 4 July 2019
*/

#ifndef LUA_UTIL_h
#define LUA_UTIL_h

#include <GarrysMod/Lua/Interface.h>

#include <cstdio>
#include <assert.h>

/// <summary>
/// A debug tool that prints the current stack in an easily readable format.
/// Helpful when trying to track down problems related to the stack.
/// </summary>
///
/// <param name="luabase"> A pointer to the current luabase. </param>
void PrintStack(GarrysMod::Lua::ILuaBase* luabase);

#endif //LUA_UTIL_h
