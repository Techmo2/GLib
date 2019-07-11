#ifndef LUA_OBJECT_BASE_
#define LUA_OBJECT_BASE_
#include "GarrysMod/Lua/Interface.h"
#include "GarrysMod/Lua/Types.h"
#include <vector>
#include <map>
#include <atomic>
#include <deque>
#include <memory>
#include <map>
#include <algorithm>
#include <string>

extern int TYPE_DATABASE;
extern int TYPE_QUERY;

class LuaObjectBase : public std::enable_shared_from_this<LuaObjectBase> {
public:
	LuaObjectBase(GarrysMod::Lua::ILuaBase* state, bool shouldthink, unsigned char type);
	LuaObjectBase(GarrysMod::Lua::ILuaBase* state, unsigned char type);
	virtual ~LuaObjectBase();
	virtual void think(GarrysMod::Lua::ILuaBase* state) = 0;
	void registerFunction(GarrysMod::Lua::ILuaBase* state, std::string name, GarrysMod::Lua::CFunc func);
	static int gcDeleteWrapper(lua_State* state);
	static int toStringWrapper(lua_State* state);
	static int createMetatables(GarrysMod::Lua::ILuaBase* state);
	static int doThink(lua_State* state);
	static LuaObjectBase* unpackSelf(GarrysMod::Lua::ILuaBase* state, int type = -1, bool shouldReference = false);
	static LuaObjectBase* unpackLuaObject(GarrysMod::Lua::ILuaBase* state, int index, int type, bool shouldReference);
	int pushTableReference(GarrysMod::Lua::ILuaBase* state);
	bool hasCallback(GarrysMod::Lua::ILuaBase* state, const char* functionName);
	int getCallbackReference(GarrysMod::Lua::ILuaBase* state, const char* functionName);
	void runFunction(GarrysMod::Lua::ILuaBase* state, int funcRef, const char* sig = 0, ...);
	void runCallback(GarrysMod::Lua::ILuaBase* state, const char* functionName, const char* sig = 0, ...);
	static std::deque<std::shared_ptr<LuaObjectBase>> luaObjects;
	static std::deque<std::shared_ptr<LuaObjectBase>> luaThinkObjects;
	static std::deque<std::shared_ptr<LuaObjectBase>> luaRemovalObjects;
	virtual void onDestroyed(GarrysMod::Lua::ILuaBase* state) {};
	std::shared_ptr<LuaObjectBase> getSharedPointerInstance();
	void unreference(GarrysMod::Lua::ILuaBase* state);
protected:
	void runFunctionVarList(GarrysMod::Lua::ILuaBase* state, int funcRef, const char* sig, va_list list);
	bool scheduledForRemoval = false;
	bool shouldthink = false;
	int m_tableReference = 0;
	int m_userdataReference = 0;
	bool canbedestroyed = true;
	const char* classname = "LuaObject";
	int type = -1;
	static void referenceTable(GarrysMod::Lua::ILuaBase* state, LuaObjectBase* object, int index);
private:
	std::map<std::string, GarrysMod::Lua::CFunc> m_callbackFunctions;
	static int tableMetaTable;
};
#endif