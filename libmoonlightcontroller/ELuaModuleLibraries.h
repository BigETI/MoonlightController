#ifndef __MOONLIGHT_CONTROLLER_E_LUA_MODULE_LIBRARY_H__
#	define __MOONLIGHT_CONTROLLER_E_LUA_MODULE_LIBRARY_H__

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// Lua module libraries enumerator
	/// </summary>
	enum ELuaModuleLibraries
	{
		/// <summary>
		/// Essential
		/// </summary>
		ELuaModuleLibraries_Essential = 0x1,

		/// <summary>
		/// Mouse
		/// </summary>
		ELuaModuleLibraries_Mouse = 0x2,

		/// <summary>
		/// Keyboard
		/// </summary>
		ELuaModuleLibraries_Keyboard = 0x4,

		/// <summary>
		/// XInput
		/// </summary>
		ELuaModuleLibraries_XInput = 0x8,

		/// <summary>
		/// Runtime
		/// </summary>
		ELuaModuleLibraries_Runtime = 0x10,

		/// <summary>
		/// Event
		/// </summary>
		ELuaModuleLibraries_Event = 0x20,

		/// <summary>
		/// Moonlight controller
		/// </summary>
		ELuaModuleLibraries_MoonlightController = ELuaModuleLibraries_Mouse | ELuaModuleLibraries_Keyboard | ELuaModuleLibraries_XInput | ELuaModuleLibraries_Event | ELuaModuleLibraries_Runtime,
		
		/// <summary>
		/// Recommended
		/// </summary>
		ELuaModuleLibraries_Recommended = ELuaModuleLibraries_Essential | ELuaModuleLibraries_MoonlightController,
		
		/// <summary>
		/// All
		/// </summary>
		ELuaModuleLibraries_All = ELuaModuleLibraries_Recommended
	};
}
#endif