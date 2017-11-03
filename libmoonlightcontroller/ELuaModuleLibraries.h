#ifndef __MOONLIGHT_CONTROLLER_E_LUA_MODULE_LIBRARY_H__
#	define __MOONLIGHT_CONTROLLER_E_LUA_MODULE_LIBRARY_H__

// Moonlight controller namespace
namespace MoonlightController
{
	// Lua module libraries enumerator
	enum ELuaModuleLibraries
	{
		// Essential
		ELuaModuleLibraries_Essential = 0x1,

		// Mouse
		ELuaModuleLibraries_Mouse = 0x2,

		// Keyboard
		ELuaModuleLibraries_Keyboard = 0x4,

		// XInput
		ELuaModuleLibraries_XInput = 0x8,

		// Runtime
		ELuaModuleLibraries_Runtime = 0x10,

		// Event
		ELuaModuleLibraries_Event = 0x20,

		// Moonlight controller
		ELuaModuleLibraries_MoonlightController = ELuaModuleLibraries_Mouse | ELuaModuleLibraries_Keyboard | ELuaModuleLibraries_XInput | ELuaModuleLibraries_Event | ELuaModuleLibraries_Runtime,
		
		// Recommended
		ELuaModuleLibraries_Recommended = ELuaModuleLibraries_Essential | ELuaModuleLibraries_MoonlightController,
		
		// All
		ELuaModuleLibraries_All = ELuaModuleLibraries_Recommended
	};
}
#endif