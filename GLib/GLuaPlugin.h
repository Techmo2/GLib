/*
	This is the plugin class. This class handles the various defined functions and registers
	them with the game when the plugin starts up.

	Author: Techmo
	Last modified: 4 July 2019
*/

#ifndef LUA_PLUGIN_h
#define LUA_PLUGIN_h

#define GMOD_ALLOW_DEPRECATED 1

#include "GIncludes.h"
#include "GLuaFunction.h"

#if defined SYSTEM_WINDOWS

static const char IServer_sig[] = "\x2A\x2A\x2A\x2A\xE8\x2A\x2A\x2A\x2A\xD8\x6D\x24\x83\x4D\xEC\x10";
static const size_t IServer_siglen = sizeof(IServer_sig) - 1;

#elif defined SYSTEM_LINUX

static const char IServer_sig[] = "@sv";
static const size_t IServer_siglen = 0;

#elif defined SYSTEM_MACOSX

static const char IServer_sig[] = "\x2A\x2A\x2A\x2A\x8B\x08\x89\x04\x24\xFF\x51\x28\xF3\x0F\x10\x45";
static const size_t IServer_siglen = sizeof(IServer_sig) - 1;

#endif

const std::string engine_lib = Helpers::GetBinaryFileName(
	"engine",
	false,
	IS_SERVERSIDE,
	"bin/"
);

const std::string server_lib = Helpers::GetBinaryFileName(
	"server",
	false,
	IS_SERVERSIDE,
	"garrysmod/bin/"
);



class GLuaPlugin {
private:
	/*
	SourceSDK::FactoryLoader* engine_loader;
	SourceSDK::FactoryLoader* server_loader;
	*/
	const char* version;
	const char* name;
	const char* tname;
	lua_State* state;
	//IVEngineServer *engine = NULL;
	//IServer *server = NULL;
	std::vector<GLuaFunction*> r_functions;
	std::vector<GLuaFunction*> r_global_functions;
public:

	/// <summary>
	/// Creates a new GLua plugin object.
	/// </summary>
	///
	/// <param name="_name"> The name of the plugin. </param>
	/// <param name="_version"> The version of the plugin. </param>
	/// <param name="_tname"> The name of the table in which to register non global functions. Keeps lua code tidy. </param>
	/// <param name="_state"> A pointer to the lua state. </param>
	GLuaPlugin(const char* _name, const char* _version, const char* _tname, lua_State* _state);
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
	void Register(GLuaFunction* _func);

	/// <summary>
	/// Caches a GLuaFunction to be registered in the global table when the plugin starts.
	/// </summary>
	///
	/// <param name="_func"> The GLuaFunction to be registered. </param>
	void RegisterGlobal(GLuaFunction* _func);

	/// <summary>
	/// Throws a lua error without halting execution of the current function.
	/// </summary>
	///
	/// <param name="error"> The error message. </param>
	void ThrowErrorSoft(const char* error);

	/// <summary>
	/// Throws a lua error and halts execution of the current function.
	/// </summary>
	///
	/// <param name="error"> The error message. </param>
	void ThrowErrorHard(const char* error);

	/// <summary>
	/// Returns a pointer to an extended lua interface.
	/// </summary>
	/// <returns> Returns a pointer to an extended lua interface. </returns>
	GarrysMod::Lua::ILuaInterface* GetLuaInterface();
};

#endif //LUA_PLUGIN_h
