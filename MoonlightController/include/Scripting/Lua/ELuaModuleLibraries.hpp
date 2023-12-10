#pragma once

#include <type_traits>

namespace MoonlightController::Scripting::Lua {

	/// <summary>
	/// Lua module libraries enumerator
	/// </summary>
	enum class ELuaModuleLibraries {

		/// <summary>
		/// Essential
		/// </summary>
		Essential = 0x1,

		/// <summary>
		/// Mouse
		/// </summary>
		Mouse = 0x2,

		/// <summary>
		/// Keyboard
		/// </summary>
		Keyboard = 0x4,

		/// <summary>
		/// XInput
		/// </summary>
		XInput = 0x8,

		/// <summary>
		/// Runtime
		/// </summary>
		Runtime = 0x10,

		/// <summary>
		/// Events
		/// </summary>
		Events = 0x20,

		/// <summary>
		/// Moonlight controller
		/// </summary>
		MoonlightController = Mouse | Keyboard | XInput | Events | Runtime,
		
		/// <summary>
		/// Recommended
		/// </summary>
		Recommended = Essential | MoonlightController,
		
		/// <summary>
		/// All
		/// </summary>
		All = Recommended
	};

	constexpr inline static ELuaModuleLibraries operator &(ELuaModuleLibraries left, ELuaModuleLibraries right) {
		return ELuaModuleLibraries(std::underlying_type<ELuaModuleLibraries>::type(left) & std::underlying_type<ELuaModuleLibraries>::type(right));
	}

	constexpr inline static ELuaModuleLibraries operator |(ELuaModuleLibraries left, ELuaModuleLibraries right) {
		return ELuaModuleLibraries(std::underlying_type<ELuaModuleLibraries>::type(left) | std::underlying_type<ELuaModuleLibraries>::type(right));
	}

	constexpr inline static ELuaModuleLibraries operator ^(ELuaModuleLibraries left, ELuaModuleLibraries right) {
		return ELuaModuleLibraries(std::underlying_type<ELuaModuleLibraries>::type(left) ^ std::underlying_type<ELuaModuleLibraries>::type(right));
	}
}
