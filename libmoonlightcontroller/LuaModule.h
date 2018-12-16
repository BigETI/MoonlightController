#ifndef __MOONLIGHT_CONTROLLER_LUA_MODULE_H__
#	define __MOONLIGHT_CONTROLLER_LUA_MODULE_H__

#	include <libmoonlightcontroller/Definitions.h>
#	include <lua.hpp>
#	include <string>
#	include <map>
#	include <vector>
#	include <locale>
#	include <codecvt>
#	include <libmoonlightcontroller/ELuaModuleLibraries.h>
#	include <libmoonlightcontroller/KeyboardController.h>
#	include <libmoonlightcontroller/MouseController.h>
#	include <libmoonlightcontroller/XInputController.h>

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// Lua module class
	/// </summary>
	class LuaModule
	{
	private:

		/// <summary>
		/// Lua state
		/// </summary>
		lua_State *luaState;

		/// <summary>
		/// Is file
		/// </summary>
		bool isFile;

		/// <summary>
		/// Source (File name or source code)
		/// </summary>
		std::string source;

		/// <summary>
		/// Exit signal
		/// </summary>
		bool exitSignal;

		/// <summary>
		/// Default contructor
		/// </summary>
		LuaModule();

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="">Lua module</param>
		LuaModule(const LuaModule &);

		/// <summary>
		/// Assign operator
		/// </summary>
		/// <param name="">Lua module</param>
		/// <returns>This</returns>
		LuaModule &operator=(const LuaModule &);

	MOONLIGHT_CONTROLLER_PRIVATE:

		/// <summary>
		/// Events
		/// </summary>
		std::map<std::string, std::vector<int>> events;

		/// <summary>
		/// Keyboard controller
		/// </summary>
		KeyboardController keyboardController;

		/// <summary>
		/// Mouse controller
		/// </summary>
		MouseController mouseController;

		/// <summary>
		/// XInput controller
		/// </summary>
		XInputController xinputController;

		/// <summary>
		/// Set exit signal
		/// </summary>
		void SetExitSignal();

	public:

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="source">Source</param>
		/// <param name="isFile">Is file</param>
		/// <param name="libraries">Libraries</param>
		LuaModule(const std::string & source, bool isFile, ELuaModuleLibraries libraries);

		/// <summary>
		/// Destructor
		/// </summary>
		~LuaModule();

		/// <summary>
		/// Is module active
		/// </summary>
		/// <returns>"true" if active, otherwise "false"</returns>
		bool IsActive();

		/// <summary>
		/// Execute module
		/// </summary>
		void Execute();

		/// <summary>
		/// Invoke event
		/// </summary>
		/// <param name="eventName">Event name</param>
		void InvokeEvent(const std::string & eventName);

		/// <summary>
		/// Close module
		/// </summary>
		void Close();
	};
}
#endif
