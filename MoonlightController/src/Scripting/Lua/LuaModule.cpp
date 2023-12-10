#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>

#include <Controllers/Keyboard/IKeyboardController.hpp>
#include <Controllers/Mouse/EMouseButton.hpp>
#include <Controllers/XInput/EXInputAxis.hpp>
#include <Controllers/XInput/EXInputBatteryDeviceType.hpp>
#include <Controllers/XInput/EXInputButtons.hpp>
#include <Controllers/XInput/IXInputController.hpp>
#include <Controllers/XInput/XInputBatteryInformation.hpp>
#include <Controllers/XInput/XInputCapabilities.hpp>
#include <Controllers/XInput/XInputControllers.hpp>
#include <Controllers/XInput/XInputKeystroke.hpp>
#include <Scripting/Lua/LuaModule.hpp>
#include <Position2D.hpp>
#include <Vector2D.hpp>

using namespace MoonlightController;
using namespace MoonlightController::Controllers::Keyboard;
using namespace MoonlightController::Controllers::Mouse;
using namespace MoonlightController::Controllers::XInput;
using namespace MoonlightController::Scripting::Lua;
using namespace std;
using namespace std::filesystem;

/// <summary>
/// Lua module luaModules
/// </summary>
unordered_map<lua_State*, LuaModule*> LuaModule::luaModules;

/// <summary>
/// Lua event invoke
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaEventInvoke(lua_State* luaState) {
	if (lua_isstring(luaState, 1)) {
		string event_name(lua_tostring(luaState, 1));
		for (const auto& lua_module : LuaModule::GetLuaModules()) {
			if (lua_module.second) {
				lua_module.second->InvokeEvent(event_name);
			}
		}
	}
	return 0;
}

/// <summary>
/// Lua event register
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaEventRegister(lua_State* luaState) {
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isstring(luaState, 1) && lua_isfunction(luaState, 2)) {
		string name = lua_tostring(luaState, 1);
		int func = luaL_ref(luaState, LUA_REGISTRYINDEX);
		auto& lua_events(lua_module->GetLuaEvents());
		const auto& it(lua_events.find(name));
		if (it == lua_events.end()) {
			lua_events.insert_or_assign(name, vector<int> { func });
		}
		else {
			it->second.push_back(func);
		}
	}
	return 0;
}

/// <summary>
/// Lua keyboard click
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaKeyboardClickKey(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const KeyboardControllers& keyboard_controllers(lua_module->GetKeyboardControllers());
		lua_pushboolean(luaState, ((controller_index >= 0) && keyboard_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && keyboard_controllers[static_cast<size_t>(controller_index)].ClickKey(static_cast<int>(lua_tointeger(luaState, 2)))) ? 1 : 0);
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua keyboard input
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaKeyboardAppendTextAsInput(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isstring(luaState, 2)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const KeyboardControllers& keyboard_controllers(lua_module->GetKeyboardControllers());
		lua_pushboolean(luaState, ((controller_index >= 0) && keyboard_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && keyboard_controllers[static_cast<size_t>(controller_index)].AppendTextAsKeystrokes(lua_tostring(luaState, 2))) ? 1 : 0);
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua keyboard is down
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaKeyboardIsKeyDown(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const KeyboardControllers& keyboard_controllers(lua_module->GetKeyboardControllers());
		lua_pushboolean(luaState, ((controller_index >= 0) && keyboard_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && keyboard_controllers[static_cast<size_t>(controller_index)].IsKeyDown(static_cast<int>(lua_tointeger(luaState, 2)))) ? 1 : 0);
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua keyboard press key
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaKeyboardPressKey(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const KeyboardControllers& keyboard_controllers(lua_module->GetKeyboardControllers());
		lua_pushboolean(luaState, ((controller_index >= 0) && keyboard_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && keyboard_controllers[static_cast<size_t>(controller_index)].PressKey(static_cast<int>(lua_tointeger(luaState, 2)))) ? 1 : 0);
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua keyboard release key
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaKeyboardReleaseKey(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const KeyboardControllers& keyboard_controllers(lua_module->GetKeyboardControllers());
		lua_pushboolean(luaState, ((controller_index >= 0) && keyboard_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && keyboard_controllers[static_cast<size_t>(controller_index)].ReleaseKey(static_cast<int>(lua_tointeger(luaState, 2)))) ? 1 : 0);
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua mouse click
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaMouseClickButton(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const MouseControllers& mouse_controllers(lua_module->GetMouseControllers());
		lua_pushboolean(luaState, ((controller_index >= 0) && mouse_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && mouse_controllers[static_cast<size_t>(controller_index)].ClickButton(static_cast<EMouseButton>(static_cast<int>(lua_tointeger(luaState, 2))))) ? 1 : 0);
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua mouse get position
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaMouseGetCursorPosition(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const MouseControllers& mouse_controllers(lua_module->GetMouseControllers());
		Position2D<int> position;
		if (mouse_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && mouse_controllers[static_cast<size_t>(controller_index)].TryGettingPosition(position)) {
			lua_pushinteger(luaState, position.x);
			lua_pushinteger(luaState, position.y);
			ret = 2;
		}
	}
	return ret;
}

/// <summary>
/// Lua mouse is down
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaMouseIsButtonDown(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const MouseControllers& mouse_controllers(lua_module->GetMouseControllers());
		lua_pushboolean(luaState, ((controller_index >= 0) && mouse_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && mouse_controllers[static_cast<size_t>(controller_index)].IsButtonDown(static_cast<EMouseButton>(lua_tointeger(luaState, 2)))) ? 1 : 0);
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua mouse move
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaMouseMoveCursor(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2) && lua_isinteger(luaState, 3)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const MouseControllers& mouse_controllers(lua_module->GetMouseControllers());
		lua_pushboolean(luaState, ((controller_index >= 0) && mouse_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && mouse_controllers[static_cast<size_t>(controller_index)].MoveCursor(static_cast<int>(lua_tointeger(luaState, 2)), static_cast<int>(lua_tointeger(luaState, 3)))) ? 1 : 0);
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua mouse press
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaMousePressButton(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const MouseControllers& mouse_controllers(lua_module->GetMouseControllers());
		lua_pushboolean(luaState, ((controller_index >= 0) && mouse_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && mouse_controllers[static_cast<size_t>(controller_index)].PressButton(static_cast<EMouseButton>(lua_tointeger(luaState, 2)))) ? 1 : 0);
		ret = 1;
	}
	return ret;
}

static int LuaMouseReleaseButton(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const MouseControllers& mouse_controllers(lua_module->GetMouseControllers());
		lua_pushboolean(luaState, ((controller_index >= 0) && mouse_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && mouse_controllers[static_cast<size_t>(controller_index)].ReleaseButton(static_cast<EMouseButton>(lua_tointeger(luaState, 2)))) ? 1 : 0);
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua mouse scroll
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaMouseScrollWheel(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const MouseControllers& mouse_controllers(lua_module->GetMouseControllers());
		lua_pushboolean(luaState, ((controller_index >= 0) && mouse_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && mouse_controllers[static_cast<size_t>(controller_index)].ScrollWheel(static_cast<int>(lua_tointeger(luaState, 2)))) ? 1 : 0);
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua mouse set position
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaMouseSetCursorPosition(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2) && lua_isinteger(luaState, 3)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const MouseControllers& mouse_controllers(lua_module->GetMouseControllers());
		lua_pushboolean(luaState, ((controller_index >= 0) && mouse_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && mouse_controllers[static_cast<size_t>(controller_index)].SetCursorPosition(static_cast<int>(lua_tointeger(luaState, 2)), static_cast<int>(lua_tointeger(luaState, 3)))) ? 1 : 0);
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua runtime exit
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaRuntimeExit(lua_State* luaState) {
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module) {
		lua_module->SetExitSignal();
	}
	return 0;
}

/// <summary>
/// Lua XInput is connected
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaXInputIsConnected(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const XInputControllers& x_input_controllers(lua_module->GetXInputControllers());
		lua_pushboolean(luaState, ((controller_index >= 0) && x_input_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && x_input_controllers[static_cast<size_t>(controller_index)].IsConnected()) ? 1 : 0);
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua XInput get buttons
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaXInputGetPressedButtons(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const XInputControllers& x_input_controllers(lua_module->GetXInputControllers());
		if ((controller_index >= 0) && x_input_controllers.IsControllerAvailable(static_cast<size_t>(controller_index))) {
			EXInputButtons buttons;
			if (x_input_controllers[static_cast<size_t>(controller_index)].TryGettingPressedButtons(buttons)) {
				lua_pushinteger(luaState, static_cast<lua_Integer>(buttons));
				ret = 1;
			}
		}
	}
	return ret;
}

// TODO: Finish implementing old style API

/// <summary>
/// Lua XInput get axis
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaXInputGetAxisValue(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const XInputControllers& x_input_controllers(lua_module->GetXInputControllers());
		float axis_value;
		if ((controller_index >= 0) && x_input_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) && x_input_controllers[static_cast<size_t>(controller_index)].TryGettingAxisValue(static_cast<EXInputAxis>(lua_tointeger(luaState, 2)), axis_value)) {
			lua_pushnumber(luaState, static_cast<lua_Number>(axis_value));
			ret = 1;
		}
	}
	return ret;
}

/// <summary>
/// Lua XInput set vibration
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaXInputSetVibration(lua_State* luaState) {
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	bool result(false);
	if (lua_module && lua_isinteger(luaState, 1) && lua_isnumber(luaState, 2) && lua_isnumber(luaState, 3)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const XInputControllers& x_input_controllers(lua_module->GetXInputControllers());
		if ((controller_index >= 0) && x_input_controllers.IsControllerAvailable(static_cast<size_t>(controller_index))) {
			x_input_controllers[static_cast<size_t>(controller_index)].SetVibration(static_cast<float>(lua_tonumber(luaState, 2)), static_cast<float>(lua_tonumber(luaState, 3)));
			result = true;
		}
	}
	lua_pushboolean(luaState, result ? 1 : 0);
	return 1;
}

/// <summary>
/// Lua XInput.getAudioDeviceIDs
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaXInputGetAudioDeviceIDs(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const XInputControllers& x_input_controllers(lua_module->GetXInputControllers());
		wstring wide_render_device_id;
		wstring wide_capture_device_id;
		if (
			(controller_index >= 0) &&
			x_input_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) &&
			x_input_controllers[static_cast<size_t>(controller_index)].TryGettingAudioDeviceIDs(wide_render_device_id, wide_capture_device_id)) {
			string render_device_id(wide_render_device_id.size(), '\0');
			string capture_device_id(wide_capture_device_id.size(), '\0');
			std::transform(
				wide_render_device_id.begin(),
				wide_render_device_id.end(),
				render_device_id.begin(),
				[](wstring::value_type character) {
					return static_cast<string::value_type>(character);
				}
			);
			std::transform(
				wide_capture_device_id.begin(),
				wide_capture_device_id.end(),
				capture_device_id.begin(),
				[](wstring::value_type character) {
					return static_cast<string::value_type>(character);
				}
			);
			lua_pushstring(luaState, render_device_id.c_str());
			lua_pushstring(luaState, capture_device_id.c_str());
			ret = 2;
		}
	}
	return ret;
}

/// <summary>
/// Lua XInput get battery information
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaXInputGetBatteryInformation(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const XInputControllers& x_input_controllers(lua_module->GetXInputControllers());
		XInputBatteryInformation battery_information;
		if (
			(controller_index >= 0) &&
			x_input_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) &&
			x_input_controllers[static_cast<size_t>(controller_index)].TryGettingBatteryInformation(
				static_cast<EXInputBatteryDeviceType>(lua_tointeger(luaState, 2)),
				battery_information
			)) {
			lua_pushinteger(luaState, static_cast<int>(battery_information.batteryType));
			lua_pushinteger(luaState, static_cast<int>(battery_information.batteryLevel));
			ret = 2;
		}
	}
	return ret;
}

/// <summary>
/// Lua XInput get capabilities
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaXInputGetCapabilities(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const XInputControllers& x_input_controllers(lua_module->GetXInputControllers());
		XInputCapabilities capabilities;
		if (
			(controller_index >= 0) &&
			x_input_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) &&
			x_input_controllers[static_cast<size_t>(controller_index)].TryGettingCapabilities(capabilities)) {
			lua_pushinteger(luaState, static_cast<int>(capabilities.deviceType));
			lua_pushinteger(luaState, static_cast<int>(capabilities.deviceSubType));
			lua_pushinteger(luaState, static_cast<int>(capabilities.deviceFeatures));
			lua_pushinteger(luaState, static_cast<int>(capabilities.buttons));
			lua_pushnumber(luaState, capabilities.leftTrigger);
			lua_pushnumber(luaState, capabilities.rightTrigger);
			lua_pushnumber(luaState, capabilities.thumbLX);
			lua_pushnumber(luaState, capabilities.thumbLY);
			lua_pushnumber(luaState, capabilities.thumbRX);
			lua_pushnumber(luaState, capabilities.thumbRY);
			lua_pushnumber(luaState, capabilities.leftMotor);
			lua_pushnumber(luaState, capabilities.rightMotor);
			ret = 12;
		}
	}
	return ret;
}

/// <summary>
/// Lua XInput get keystroke
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int LuaXInputGetKeystroke(lua_State* luaState) {
	int ret(0);
	LuaModule* lua_module(LuaModule::GetLuaModules().at(luaState));
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2)) {
		int controller_index(static_cast<int>(lua_tointeger(luaState, 1)) - 1);
		const XInputControllers& x_input_controllers(lua_module->GetXInputControllers());
		XInputKeystroke keystroke;
		if (
			(controller_index >= 0) &&
			x_input_controllers.IsControllerAvailable(static_cast<size_t>(controller_index)) &&
			x_input_controllers[static_cast<size_t>(controller_index)].TryGettingKeystroke(keystroke)) {
			lua_pushinteger(luaState, static_cast<int>(keystroke.virtualKey));
			lua_pushinteger(luaState, static_cast<int>(keystroke.unicode));
			lua_pushinteger(luaState, static_cast<int>(keystroke.keyboardStates));
			lua_pushinteger(luaState, keystroke.userIndex);
			lua_pushinteger(luaState, keystroke.hidCode);
			ret = 5;
		}
	}
	return ret;
}

/// <summary>
/// Event library
/// </summary>
static const luaL_Reg eventLibrary[] = {
	{ "invokeEvent", LuaEventInvoke },
	{ "registerEvent", LuaEventRegister },
	{ nullptr, nullptr }
};

/// <summary>
/// Keyboard library
/// </summary>
static const luaL_Reg keyboardLibrary[] = {
	{ "clickKey", LuaKeyboardClickKey },
	{ "appendTextAsInput", LuaKeyboardAppendTextAsInput },
	{ "isKeyDown", LuaKeyboardIsKeyDown },
	{ "pressKey", LuaKeyboardPressKey },
	{ "releaseKey", LuaKeyboardReleaseKey },
	{ nullptr, nullptr }
};

/// <summary>
/// Mouse library
/// </summary>
static const luaL_Reg mouseLibrary[] = {
	{ "clickButton", LuaMouseClickButton },
	{ "getCursorPosition", LuaMouseGetCursorPosition },
	{ "isButtonDown", LuaMouseIsButtonDown },
	{ "moveCursor", LuaMouseMoveCursor },
	{ "pressButton", LuaMousePressButton },
	{ "releaseButton", LuaMouseReleaseButton },
	{ "scrollWheel", LuaMouseScrollWheel },
	{ "setCursorPosition", LuaMouseSetCursorPosition },
	{ nullptr, nullptr }
};

/// <summary>
/// XInput library
/// </summary>
static const luaL_Reg xInputLibrary[] = {
	{ "getAudioDeviceIDs", LuaXInputGetAudioDeviceIDs },
	{ "getAxisValue", LuaXInputGetAxisValue },
	{ "getBatteryInformation", LuaXInputGetBatteryInformation },
	{ "getPressedButtons", LuaXInputGetPressedButtons },
	{ "getCapabilities", LuaXInputGetCapabilities },
	{ "getKeystroke", LuaXInputGetKeystroke },
	{ "isConnected", LuaXInputIsConnected },
	{ "setVibration", LuaXInputSetVibration },
	{ nullptr, nullptr }
};

/// <summary>
/// Runtime library
/// </summary>
static const luaL_Reg runtimeLibrary[] = {
	{ "exit", LuaRuntimeExit },
	{ nullptr, nullptr }
};

LuaModule::LuaModule(const path& filePath, ELuaModuleLibraries libraries) : luaState(nullptr), exitSignal(false) {
	luaState = luaL_newstate();
	if (luaState) {
		luaModules.insert_or_assign(luaState, this);
		InitializeLibraries(libraries);
		string file_path(filePath.string());
		if (luaL_loadfile(luaState, file_path.c_str())) {
			cerr << lua_tostring(luaState, -1) << endl;
			Close();
		}
	}
}

LuaModule::LuaModule(string_view sourceCode, ELuaModuleLibraries libraries) : luaState(nullptr), exitSignal(false) {
	luaState = luaL_newstate();
	if (luaState) {
		luaModules.insert_or_assign(luaState, this);
		InitializeLibraries(libraries);
		if (luaL_loadstring(luaState, sourceCode.data())) {
			cerr << lua_tostring(luaState, -1) << endl;
			Close();
		}
	}
}

LuaModule::~LuaModule() {
	Close();
}

void LuaModule::InitializeLibraries(ELuaModuleLibraries libraries) {
	if ((libraries & ELuaModuleLibraries::Essential) == ELuaModuleLibraries::Essential) {
		luaL_openlibs(luaState);
	}
	if ((libraries & ELuaModuleLibraries::Mouse) == ELuaModuleLibraries::Mouse) {
		lua_newtable(luaState);
		luaL_setfuncs(luaState, mouseLibrary, 0);
		lua_pushinteger(luaState, static_cast<lua_Integer>(MouseControllers::GetMaximalControllerCount()));
		lua_setfield(luaState, -2, "maximalControllerCount");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EMouseButton::Left));
		lua_setfield(luaState, -2, "left");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EMouseButton::Right));
		lua_setfield(luaState, -2, "right");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EMouseButton::Middle));
		lua_setfield(luaState, -2, "middle");
		lua_pushvalue(luaState, -1);
		lua_setglobal(luaState, "mouse");
	}
	if ((libraries & ELuaModuleLibraries::Keyboard) == ELuaModuleLibraries::Keyboard) {
		lua_newtable(luaState);
		luaL_setfuncs(luaState, keyboardLibrary, 0);
		lua_pushinteger(luaState, static_cast<lua_Integer>(KeyboardControllers::GetMaximalControllerCount()));
		lua_setfield(luaState, -2, "maximalControllerCount");
		lua_pushvalue(luaState, -1);
		lua_setglobal(luaState, "keyboard");
	}
	if ((libraries & ELuaModuleLibraries::XInput) == ELuaModuleLibraries::XInput) {
		lua_newtable(luaState);
		luaL_setfuncs(luaState, xInputLibrary, 0);
		lua_pushinteger(luaState, static_cast<lua_Integer>(XInputControllers::GetMaximalControllerCount()));
		lua_setfield(luaState, -2, "maximalControllerCount");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputButtons::DPadUp));
		lua_setfield(luaState, -2, "dPadUp");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputButtons::DPadDown));
		lua_setfield(luaState, -2, "dPadDown");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputButtons::DPadLeft));
		lua_setfield(luaState, -2, "dPadLeft");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputButtons::DPadRight));
		lua_setfield(luaState, -2, "dPadRight");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputButtons::Start));
		lua_setfield(luaState, -2, "start");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputButtons::Back));
		lua_setfield(luaState, -2, "back");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputButtons::LeftThumb));
		lua_setfield(luaState, -2, "leftThumb");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputButtons::RightThumb));
		lua_setfield(luaState, -2, "rightThumb");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputButtons::LeftShoulder));
		lua_setfield(luaState, -2, "leftShoulder");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputButtons::RightShoulder));
		lua_setfield(luaState, -2, "rightShoulder");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputButtons::A));
		lua_setfield(luaState, -2, "a");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputButtons::B));
		lua_setfield(luaState, -2, "b");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputButtons::X));
		lua_setfield(luaState, -2, "x");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputButtons::Y));
		lua_setfield(luaState, -2, "y");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputAxis::ThumbLX));
		lua_setfield(luaState, -2, "thumbLX");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputAxis::ThumbLY));
		lua_setfield(luaState, -2, "thumbLY");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputAxis::ThumbRX));
		lua_setfield(luaState, -2, "thumbRX");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputAxis::ThumbRY));
		lua_setfield(luaState, -2, "thumbRY");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputAxis::LeftTrigger));
		lua_setfield(luaState, -2, "leftTrigger");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputAxis::RightTrigger));
		lua_setfield(luaState, -2, "rightTrigger");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputBatteryLevel::Empty));
		lua_setfield(luaState, -2, "batteryLevelEmpty");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputBatteryLevel::Low));
		lua_setfield(luaState, -2, "batteryLevelLow");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputBatteryLevel::Medium));
		lua_setfield(luaState, -2, "batteryLevelMedium");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputBatteryLevel::Full));
		lua_setfield(luaState, -2, "batteryLevelFull");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputBatteryType::Disconnected));
		lua_setfield(luaState, -2, "batteryTypeDisconnected");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputBatteryType::Wired));
		lua_setfield(luaState, -2, "batteryTypeWired");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputBatteryType::Alkaline));
		lua_setfield(luaState, -2, "batteryTypeAlkaline");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputBatteryType::NiMH));
		lua_setfield(luaState, -2, "batteryTypeNiMH");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputBatteryType::Unknown));
		lua_setfield(luaState, -2, "batteryTypeUnknown");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputDeviceType::Gamepad));
		lua_setfield(luaState, -2, "deviceTypeGamepad");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputBatteryDeviceType::Gamepad));
		lua_setfield(luaState, -2, "batteryDeviceTypeGamepad");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputBatteryDeviceType::Headset));
		lua_setfield(luaState, -2, "batteryDeviceTypeHeadset");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputDeviceSubType::Unknown));
		lua_setfield(luaState, -2, "deviceSubTypeUnknown");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputDeviceSubType::Gamepad));
		lua_setfield(luaState, -2, "deviceSubTypeGamepad");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputDeviceSubType::Wheel));
		lua_setfield(luaState, -2, "deviceSubTypeWheel");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputDeviceSubType::ArcadeStick));
		lua_setfield(luaState, -2, "deviceSubTypeArcadeStick");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputDeviceSubType::FlightStick));
		lua_setfield(luaState, -2, "deviceSubTypeFlightStick");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputDeviceSubType::DancePad));
		lua_setfield(luaState, -2, "deviceSubTypeDancePad");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputDeviceSubType::Guitar));
		lua_setfield(luaState, -2, "deviceSubTypeGuitar");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputDeviceSubType::GuitarAlternate));
		lua_setfield(luaState, -2, "deviceSubTypeGuitarAlternate");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputDeviceSubType::GuitarBass));
		lua_setfield(luaState, -2, "deviceSubTypeGuitarBass");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputDeviceSubType::DrumKit));
		lua_setfield(luaState, -2, "deviceSubTypeDrumKit");
		lua_pushinteger(luaState, static_cast<lua_Integer>(EXInputDeviceSubType::ArcadePad));
		lua_setfield(luaState, -2, "deviceSubTypeArcadePad");
		lua_pushvalue(luaState, -1);
		lua_setglobal(luaState, "xinput");
	}
	if ((libraries & ELuaModuleLibraries::Runtime) == ELuaModuleLibraries::Runtime) {
		lua_newtable(luaState);
		luaL_setfuncs(luaState, runtimeLibrary, 0);
		lua_pushvalue(luaState, -1);
		lua_setglobal(luaState, "runtime");
	}
	if ((libraries & ELuaModuleLibraries::Events) == ELuaModuleLibraries::Events) {
		lua_newtable(luaState);
		luaL_setfuncs(luaState, eventLibrary, 0);
		lua_pushvalue(luaState, -1);
		lua_setglobal(luaState, "events");
	}
}

const std::unordered_map<lua_State*, LuaModule*>& LuaModule::GetLuaModules() noexcept {
	return luaModules;
}

const std::unordered_map<std::string, std::vector<int>>& LuaModule::GetLuaEvents() const noexcept {
	return luaEvents;
}

std::unordered_map<std::string, std::vector<int>>& LuaModule::GetLuaEvents() noexcept {
	return luaEvents;
}

const KeyboardControllers& LuaModule::GetKeyboardControllers() const noexcept {
	return keyboardControllers;
}

KeyboardControllers& LuaModule::GetKeyboardControllers() noexcept {
	return keyboardControllers;
}

const MouseControllers& LuaModule::GetMouseControllers() const noexcept {
	return mouseControllers;
}

MouseControllers& LuaModule::GetMouseControllers() noexcept {
	return mouseControllers;
}

const XInputControllers& LuaModule::GetXInputControllers() const noexcept {
	return xInputControllers;
}

XInputControllers& LuaModule::GetXInputControllers() noexcept {
	return xInputControllers;
}

bool LuaModule::IsActive() const noexcept {
	return (luaState != nullptr);
}

void LuaModule::Execute() noexcept {
	if (luaState) {
		if (lua_pcall(luaState, 0, LUA_MULTRET, 0)) {
			cerr << lua_tostring(luaState, -1) << endl;
			Close();
		}
		if (exitSignal) {
			Close();
		}
	}
}

void LuaModule::InvokeEvent(const string& eventName) noexcept {
	if (luaState) {
		const auto& it(luaEvents.find(eventName));
		if (it != luaEvents.end()) {
			for (int function : it->second) {
				lua_rawgeti(luaState, LUA_REGISTRYINDEX, function);
				if (lua_pcall(luaState, 0, LUA_MULTRET, 0)) {
					cerr << lua_tostring(luaState, -1) << endl;
					Close();
					break;
				}
			}
		}
		if (exitSignal) {
			Close();
		}
	}
}

bool LuaModule::Close() noexcept {
	bool ret(static_cast<bool>(luaState));
	if (ret) {
		lua_close(luaState);
		luaModules.erase(luaState);
		luaState = nullptr;
	}
	return ret;
}

void LuaModule::SetExitSignal() noexcept {
	exitSignal = true;
}
