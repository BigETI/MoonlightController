#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <lua.hpp>

#include "../../Controllers/Keyboard/KeyboardControllers.hpp"
#include "../../Controllers/Mouse/MouseControllers.hpp"
#include "../../Controllers/XInput/IXInputController.hpp"
#include "../../Controllers/XInput/XInputControllers.hpp"
#include "../../Exportables/Exportable.hxx"
#include "ELuaModuleLibraries.hpp"

namespace MoonlightController::Scripting::Lua
{
	/// <summary>
	/// Lua module class
	/// </summary>
	class LuaModule {
	public:

		LuaModule() = delete;
		LuaModule(const LuaModule&) = delete;
		LuaModule(LuaModule&&) noexcept = delete;

		MOONLIGHT_CONTROLLER_API LuaModule(const std::filesystem::path& filePath, ELuaModuleLibraries libraries);

		MOONLIGHT_CONTROLLER_API LuaModule(std::string_view sourceCode, ELuaModuleLibraries libraries);

		MOONLIGHT_CONTROLLER_API ~LuaModule();

		MOONLIGHT_CONTROLLER_API static const std::unordered_map<lua_State*, LuaModule*>& GetLuaModules() noexcept;

		MOONLIGHT_CONTROLLER_API const std::unordered_map<std::string, std::vector<int>>& GetLuaEvents() const noexcept;

		MOONLIGHT_CONTROLLER_API std::unordered_map<std::string, std::vector<int>>& GetLuaEvents() noexcept;

		MOONLIGHT_CONTROLLER_API const MoonlightController::Controllers::Keyboard::KeyboardControllers& GetKeyboardControllers() const noexcept;
		
		MOONLIGHT_CONTROLLER_API MoonlightController::Controllers::Keyboard::KeyboardControllers& GetKeyboardControllers() noexcept;

		MOONLIGHT_CONTROLLER_API const MoonlightController::Controllers::Mouse::MouseControllers& GetMouseControllers() const noexcept;

		MOONLIGHT_CONTROLLER_API MoonlightController::Controllers::Mouse::MouseControllers& GetMouseControllers() noexcept;

		MOONLIGHT_CONTROLLER_API const MoonlightController::Controllers::XInput::XInputControllers& GetXInputControllers() const noexcept;

		MOONLIGHT_CONTROLLER_API MoonlightController::Controllers::XInput::XInputControllers& GetXInputControllers() noexcept;

		MOONLIGHT_CONTROLLER_API bool IsActive() const noexcept;

		MOONLIGHT_CONTROLLER_API void Execute() noexcept;

		MOONLIGHT_CONTROLLER_API void InvokeEvent(const std::string& eventName) noexcept;

		MOONLIGHT_CONTROLLER_API bool Close() noexcept;

		MOONLIGHT_CONTROLLER_API void SetExitSignal() noexcept;

		LuaModule& operator =(const LuaModule&) = delete;
		LuaModule& operator =(LuaModule&&) noexcept = delete;

	private:

		static std::unordered_map<lua_State*, LuaModule*> luaModules;

		/// <summary>
		/// Lua state
		/// </summary>
		lua_State* luaState;

		/// <summary>
		/// Source code or file path
		/// </summary>
		std::string sourceCodeOrFilePath;

		/// <summary>
		/// Exit signal
		/// </summary>
		volatile bool exitSignal;

		/// <summary>
		/// Lua events
		/// </summary>
		std::unordered_map<std::string, std::vector<int>> luaEvents;

		/// <summary>
		/// Keyboard controllers
		/// </summary>
		MoonlightController::Controllers::Keyboard::KeyboardControllers keyboardControllers;

		/// <summary>
		/// Mouse controllers
		/// </summary>
		MoonlightController::Controllers::Mouse::MouseControllers mouseControllers;

		/// <summary>
		/// XInput controllers
		/// </summary>
		MoonlightController::Controllers::XInput::XInputControllers xInputControllers;

		/// <summary>
		/// Initializes the specified libraries
		/// </summary>
		void InitializeLibraries(ELuaModuleLibraries libraries);
	};
}
