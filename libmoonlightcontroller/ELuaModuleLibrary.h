#ifndef __MOONLIGHT_CONTROLLER_E_LUA_MODULE_LIBRARY_H__
#	define __MOONLIGHT_CONTROLLER_E_LUA_MODULE_LIBRARY_H__
namespace MoonlightController
{
	enum ELuaModuleLibrary
	{
		ELuaModuleLibrary_Essential = 0x1,
		ELuaModuleLibrary_Mouse = 0x2,
		ELuaModuleLibrary_Keyboard = 0x4,
		ELuaModuleLibrary_XInput = 0x8,
		ELuaModuleLibrary_Runtime = 0x10,
		ELuaModuleLibrary_Event = 0x20,
		ELuaModuleLibrary_MoonlightController = ELuaModuleLibrary_Mouse | ELuaModuleLibrary_Keyboard | ELuaModuleLibrary_XInput | ELuaModuleLibrary_Event | ELuaModuleLibrary_Runtime,
		ELuaModuleLibrary_Recommended = ELuaModuleLibrary_Essential | ELuaModuleLibrary_MoonlightController,
		ELuaModuleLibrary_All = ELuaModuleLibrary_Recommended
	};
}
#endif