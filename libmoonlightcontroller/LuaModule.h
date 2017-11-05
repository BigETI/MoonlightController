#ifndef __MOONLIGHT_CONTROLLER_LUA_MODULE_H__
#	define __MOONLIGHT_CONTROLLER_LUA_MODULE_H__

#	include <libmoonlightcontroller/Definitions.h>
#	include <lua.hpp>
#	include <string>
#	include <map>
#	include <vector>
#	include <libmoonlightcontroller/ELuaModuleLibraries.h>
#	include <libmoonlightcontroller/KeyboardController.h>
#	include <libmoonlightcontroller/MouseController.h>
#	include <libmoonlightcontroller/XInputController.h>

// Moonlight controller namespace
namespace MoonlightController
{
	// Lua module class
	class LuaModule
	{
	private:

		// Lua state
		lua_State *luaState;

		// Is file
		bool isFile;

		// Source (File name or source code)
		std::string source;

		// Exit signal
		bool exitSignal;

		// Default contructor
		LuaModule();

		// Copy constructor
		LuaModule(const LuaModule &);

		// Assign operator
		LuaModule &operator=(const LuaModule &);

	MOONLIGHT_CONTROLLER_PRIVATE:

		// Events
		std::map<std::string, std::vector<int>> events;

		// Keyboard controller
		KeyboardController keyboardController;
		
		// Mouse controller
		MouseController mouseController;

		// XInput controller
		XInputController xinputController;

		// Set exit signal
		void SetExitSignal();

	public:

		// Constructor
		LuaModule(std::string _source, bool _isFile, ELuaModuleLibraries libraries);

		// Destructor
		~LuaModule();

		// Is module active
		bool IsActive();

		// Execute module
		void Execute();

		// Invoke event
		void InvokeEvent(std::string eventName);

		// Close module
		void Close();
	};
}
#endif
