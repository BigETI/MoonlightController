#define MOONLIGHT_CONTROLLER_LIBRARY
#include <iostream>
#include <libmoonlightcontroller/LuaModule.h>

using namespace MoonlightController;
using namespace std;

/// <summary>
/// Charset converter
/// </summary>
static wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

/// <summary>
/// Lua module instances
/// </summary>
static map<lua_State *, LuaModule *> instances;

/// <summary>
/// Lua event invoke
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int event_invoke(lua_State *luaState)
{
	if (lua_isstring(luaState, 1))
	{
		string name = lua_tostring(luaState, 1);
		for (const pair<lua_State *, LuaModule *> & instance : instances)
		{
			if (instance.second)
			{
				instance.second->InvokeEvent(name);
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
int event_register(lua_State *luaState)
{
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isstring(luaState, 1) && lua_isfunction(luaState, 2))
	{
		string name = lua_tostring(luaState, 1);
		int func = luaL_ref(luaState, LUA_REGISTRYINDEX);
		map<string, vector<int>>::iterator it(lua_module->events.find(name));
		if (it == lua_module->events.end())
		{
			lua_module->events.insert(pair<string, vector<int>>(name, { func }));
		}
		else
		{
			lua_module->events[name].push_back(func);
		}
	}
	return 0;
}

/// <summary>
/// Lua keyboard click
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int keyboard_click(lua_State *luaState)
{
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1))
	{
		lua_module->keyboardController.Click(static_cast<int>(lua_tointeger(luaState, 1)));
	}
	return 0;
}

/// <summary>
/// Lua keyboard input
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int keyboard_input(lua_State *luaState)
{
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isstring(luaState, 1))
	{
		lua_module->keyboardController.Input(lua_tostring(luaState, 1));
	}
	return 0;
}

/// <summary>
/// Lua keyboard is down
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int keyboard_isDown(lua_State *luaState)
{
	int ret(0);
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1))
	{
		lua_pushboolean(luaState, lua_module->keyboardController.IsDown(static_cast<int>(lua_tointeger(luaState, 1))));
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua keyboard press
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int keyboard_press(lua_State *luaState)
{
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1) && lua_isboolean(luaState, 2))
	{
		lua_module->keyboardController.Press(static_cast<int>(lua_tointeger(luaState, 1)), lua_toboolean(luaState, 2));
	}
	return 0;
}

/// <summary>
/// Lua mouse click
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int mouse_click(lua_State *luaState)
{
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1))
	{
		lua_module->mouseController.Click(static_cast<EMouseButton>(static_cast<int>(lua_tointeger(luaState, 1))));
	}
	return 0;
}

/// <summary>
/// Lua mouse get position
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int mouse_getPosition(lua_State *luaState)
{
	int ret(0);
	LuaModule *lua_module(instances[luaState]);
	if (lua_module)
	{
		Position position;
		lua_module->mouseController.GetPosition(position);
		lua_pushinteger(luaState, position.x);
		lua_pushinteger(luaState, position.y);
		ret = 2;
	}
	return ret;
}

/// <summary>
/// Lua mouse is down
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int mouse_isDown(lua_State *luaState)
{
	int ret(0);
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1))
	{
		lua_pushboolean(luaState, lua_module->mouseController.IsDown(static_cast<EMouseButton>(lua_tointeger(luaState, 1))));
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua mouse move
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int mouse_move(lua_State *luaState)
{
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2))
	{
		lua_module->mouseController.Move(static_cast<int>(lua_tointeger(luaState, 1)), static_cast<int>(lua_tointeger(luaState, 2)));
	}
	return 0;
}

/// <summary>
/// Lua mouse press
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int mouse_press(lua_State *luaState)
{
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1) && lua_isboolean(luaState, 2))
	{
		lua_module->mouseController.Press(static_cast<EMouseButton>(static_cast<int>(lua_tointeger(luaState, 1))), lua_toboolean(luaState, 2));
	}
	return 0;
}

/// <summary>
/// Lua mouse scroll
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int mouse_scroll(lua_State *luaState)
{
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1))
	{
		lua_module->mouseController.Scroll(static_cast<int>(lua_tointeger(luaState, 1)));
	}
	return 0;
}

/// <summary>
/// Lua mouse set position
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
static int mouse_setPosition(lua_State *luaState)
{
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2))
	{
		lua_module->mouseController.SetPosition(static_cast<int>(lua_tointeger(luaState, 1)), static_cast<int>(lua_tointeger(luaState, 2)));
	}
	return 0;
}

/// <summary>
/// Lua runtime exit
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int runtime_exit(lua_State *luaState)
{
	LuaModule *lua_module(instances[luaState]);
	if (lua_module)
	{
		lua_module->SetExitSignal();
	}
	return 0;
}

/// <summary>
/// Lua XInput is connected
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int xinput_isConnected(lua_State *luaState)
{
	int ret(0);
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1))
	{
		lua_pushboolean(luaState, lua_module->xinputController.IsConnected(static_cast<int>(lua_tointeger(luaState, 1)) - 1));
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua XInput get buttons
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int xinput_getButtons(lua_State *luaState)
{
	int ret(0);
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1))
	{
		lua_pushinteger(luaState, lua_module->xinputController.GetButtons(static_cast<int>(lua_tointeger(luaState, 1)) - 1));
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua XInput get axis
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int xinput_getAxis(lua_State *luaState)
{
	int ret(0);
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2))
	{
		lua_pushnumber(luaState, lua_module->xinputController.GetAxis(static_cast<int>(lua_tointeger(luaState, 1)) - 1, static_cast<EXInputAxis>(lua_tointeger(luaState, 2))));
		ret = 1;
	}
	return ret;
}

/// <summary>
/// Lua XInput set vibration
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int xinput_setVibration(lua_State *luaState)
{
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1) && lua_isnumber(luaState, 2) && lua_isnumber(luaState, 3))
	{
		lua_module->xinputController.SetVibration(static_cast<int>(lua_tointeger(luaState, 1)) - 1, static_cast<float>(lua_tonumber(luaState, 2)), static_cast<float>(lua_tonumber(luaState, 3)));
	}
	return 0;
}

/// <summary>
/// Lua XInput.getAudioDeviceIDs
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int xinput_getAudioDeviceIDs(lua_State *luaState)
{
	int ret(0);
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1))
	{
		wstring render_device_id;
		wstring capture_device_id;
		lua_module->xinputController.GetAudioDeviceIDs(static_cast<int>(lua_tointeger(luaState, 1)) - 1, render_device_id, capture_device_id);
		lua_pushstring(luaState, converter.to_bytes(render_device_id).c_str());
		lua_pushstring(luaState, converter.to_bytes(capture_device_id).c_str());
		ret = 2;
	}
	return ret;
}

/// <summary>
/// Lua XInput get battery information
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int xinput_getBatteryInformation(lua_State *luaState)
{
	int ret(0);
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2))
	{
		XInputBatteryInformation batteryInformation;
		lua_module->xinputController.GetBatteryInformation(static_cast<int>(lua_tointeger(luaState, 1)) - 1, static_cast<EXInputBatteryDeviceType>(lua_tointeger(luaState, 2)), batteryInformation);
		lua_pushinteger(luaState, static_cast<int>(batteryInformation.batteryType));
		lua_pushinteger(luaState, static_cast<int>(batteryInformation.batteryLevel));
		ret = 2;
	}
	return ret;
}

/// <summary>
/// Lua XInput get capabilities
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int xinput_getCapabilities(lua_State *luaState)
{
	int ret(0);
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2))
	{
		XInputCapabilities capabilities;
		lua_module->xinputController.GetCapabilities(static_cast<int>(lua_tointeger(luaState, 1)) - 1, capabilities);
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
	return ret;
}

/// <summary>
/// Lua XInput get keystroke
/// </summary>
/// <param name="luaState">Lua state</param>
/// <returns>Number of return values</returns>
int xinput_getKeystroke(lua_State *luaState)
{
	int ret(0);
	LuaModule *lua_module(instances[luaState]);
	if (lua_module && lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2))
	{
		XInputKeystroke keystroke;
		lua_module->xinputController.GetKeystroke(static_cast<int>(lua_tointeger(luaState, 1)) - 1, keystroke);
		lua_pushinteger(luaState, static_cast<int>(keystroke.virtualKey));
		lua_pushinteger(luaState, static_cast<int>(keystroke.unicode));
		lua_pushinteger(luaState, static_cast<int>(keystroke.keyboardStates));
		lua_pushinteger(luaState, keystroke.userIndex);
		lua_pushinteger(luaState, keystroke.hidCode);
		ret = 5;
	}
	return ret;
}

/// <summary>
/// Event library
/// </summary>
static const luaL_Reg eventLibrary[] =
{
	{ "invoke", event_invoke },
	{ "register", event_register },
	{ nullptr, nullptr }
};

/// <summary>
/// Keyboard library
/// </summary>
static const luaL_Reg keyboardLibrary[] =
{
	{ "click", keyboard_click },
	{ "input", keyboard_input },
	{ "isDown", keyboard_isDown },
	{ "press", keyboard_press },
	{ nullptr, nullptr }
};

/// <summary>
/// Mouse library
/// </summary>
static const luaL_Reg mouseLibrary[] = {
	{ "click", mouse_click },
	{ "getPosition", mouse_getPosition },
	{ "isDown", mouse_isDown },
	{ "move", mouse_move },
	{ "press", mouse_press },
	{ "scroll", mouse_scroll },
	{ "setPosition", mouse_setPosition },
	{ nullptr, nullptr }
};

/// <summary>
/// XInput library
/// </summary>
static const luaL_Reg xInputLibrary[] =
{
	{ "getAudioDeviceIDs", xinput_getAudioDeviceIDs },
	{ "getAxis", xinput_getAxis },
	{ "getBatteryInformation", xinput_getBatteryInformation },
	{ "getButtons", xinput_getButtons },
	{ "getCapabilities", xinput_getCapabilities },
	{ "getKeystroke", xinput_getKeystroke },
	{ "isConnected", xinput_isConnected },
	{ "setVibration", xinput_setVibration },
	{ nullptr, nullptr }
};

/// <summary>
/// Runtime library
/// </summary>
static const luaL_Reg runtimeLibrary[] =
{
	{ "exit", runtime_exit },
	{ nullptr, nullptr }
};

/// <summary>
/// Set exit signal
/// </summary>
void LuaModule::SetExitSignal()
{
	exitSignal = true;
}

/// <summary>
/// Constructor
/// </summary>
/// <param name="source">Source</param>
/// <param name="isFile">Is file</param>
/// <param name="libraries">Libraries</param>
LuaModule::LuaModule(const string & source, bool isFile, ELuaModuleLibraries libraries) : source(source), isFile(isFile), luaState(nullptr), exitSignal(false)
{
	luaState = luaL_newstate();
	if (luaState)
	{
		instances[luaState] = this;
		if (libraries & ELuaModuleLibraries_Essential)
		{
			luaL_openlibs(luaState);
		}
		if (libraries & ELuaModuleLibraries_Mouse)
		{
			lua_newtable(luaState);
			luaL_setfuncs(luaState, mouseLibrary, 0);
			lua_pushinteger(luaState, EMouseButton_Left);
			lua_setfield(luaState, -2, "left");
			lua_pushinteger(luaState, EMouseButton_Right);
			lua_setfield(luaState, -2, "right");
			lua_pushinteger(luaState, EMouseButton_Middle);
			lua_setfield(luaState, -2, "middle");
			lua_pushvalue(luaState, -1);
			lua_setglobal(luaState, "mouse");
		}
		if (libraries & ELuaModuleLibraries_Keyboard)
		{
			lua_newtable(luaState);
			luaL_setfuncs(luaState, keyboardLibrary, 0);
			lua_pushvalue(luaState, -1);
			lua_setglobal(luaState, "keyboard");
		}
		if (libraries & ELuaModuleLibraries_XInput)
		{
			lua_newtable(luaState);
			luaL_setfuncs(luaState, xInputLibrary, 0);
			lua_pushinteger(luaState, static_cast<int>(XInputController::MaxControllers));
			lua_setfield(luaState, -2, "maxControllers");
			lua_pushinteger(luaState, EXInputButton_DPadUp);
			lua_setfield(luaState, -2, "dPadUp");
			lua_pushinteger(luaState, EXInputButton_DPadDown);
			lua_setfield(luaState, -2, "dPadDown");
			lua_pushinteger(luaState, EXInputButton_DPadLeft);
			lua_setfield(luaState, -2, "dPadLeft");
			lua_pushinteger(luaState, EXInputButton_DPadRight);
			lua_setfield(luaState, -2, "dPadRight");
			lua_pushinteger(luaState, EXInputButton_Start);
			lua_setfield(luaState, -2, "start");
			lua_pushinteger(luaState, EXInputButton_Back);
			lua_setfield(luaState, -2, "back");
			lua_pushinteger(luaState, EXInputButton_LeftThumb);
			lua_setfield(luaState, -2, "leftThumb");
			lua_pushinteger(luaState, EXInputButton_RightThumb);
			lua_setfield(luaState, -2, "rightThumb");
			lua_pushinteger(luaState, EXInputButton_LeftShoulder);
			lua_setfield(luaState, -2, "leftShoulder");
			lua_pushinteger(luaState, EXInputButton_RightShoulder);
			lua_setfield(luaState, -2, "rightShoulder");
			lua_pushinteger(luaState, EXInputButton_A);
			lua_setfield(luaState, -2, "a");
			lua_pushinteger(luaState, EXInputButton_B);
			lua_setfield(luaState, -2, "b");
			lua_pushinteger(luaState, EXInputButton_X);
			lua_setfield(luaState, -2, "x");
			lua_pushinteger(luaState, EXInputButton_Y);
			lua_setfield(luaState, -2, "y");
			lua_pushinteger(luaState, EXInputAxis_ThumbLX);
			lua_setfield(luaState, -2, "thumbLX");
			lua_pushinteger(luaState, EXInputAxis_ThumbLY);
			lua_setfield(luaState, -2, "thumbLY");
			lua_pushinteger(luaState, EXInputAxis_ThumbRX);
			lua_setfield(luaState, -2, "thumbRX");
			lua_pushinteger(luaState, EXInputAxis_ThumbRY);
			lua_setfield(luaState, -2, "thumbRY");
			lua_pushinteger(luaState, EXInputAxis_LeftTrigger);
			lua_setfield(luaState, -2, "leftTrigger");
			lua_pushinteger(luaState, EXInputAxis_RightTrigger);
			lua_setfield(luaState, -2, "rightTrigger");
			lua_pushinteger(luaState, EXInputBatteryLevel_Empty);
			lua_setfield(luaState, -2, "batteryLevelEmpty");
			lua_pushinteger(luaState, EXInputBatteryLevel_Low);
			lua_setfield(luaState, -2, "batteryLevelLow");
			lua_pushinteger(luaState, EXInputBatteryLevel_Medium);
			lua_setfield(luaState, -2, "batteryLevelMedium");
			lua_pushinteger(luaState, EXInputBatteryLevel_Full);
			lua_setfield(luaState, -2, "batteryLevelFull");
			lua_pushinteger(luaState, EXInputBatteryType_Disconnected);
			lua_setfield(luaState, -2, "batteryTypeDisconnected");
			lua_pushinteger(luaState, EXInputBatteryType_Wired);
			lua_setfield(luaState, -2, "batteryTypeWired");
			lua_pushinteger(luaState, EXInputBatteryType_Alkaline);
			lua_setfield(luaState, -2, "batteryTypeAlkaline");
			lua_pushinteger(luaState, EXInputBatteryType_NiMH);
			lua_setfield(luaState, -2, "batteryTypeNiMH");
			lua_pushinteger(luaState, EXInputBatteryType_Unknown);
			lua_setfield(luaState, -2, "batteryTypeUnknown");
			lua_pushinteger(luaState, EXInputDeviceType_Gamepad);
			lua_setfield(luaState, -2, "deviceTypeGamepad");
			lua_pushinteger(luaState, EXInputBatteryDeviceType_Gamepad);
			lua_setfield(luaState, -2, "batteryDeviceTypeGamepad");
			lua_pushinteger(luaState, EXInputBatteryDeviceType_Headset);
			lua_setfield(luaState, -2, "batteryDeviceTypeHeadset");
			lua_pushinteger(luaState, EXInputDeviceSubType_Unknown);
			lua_setfield(luaState, -2, "deviceSubTypeUnknown");
			lua_pushinteger(luaState, EXInputDeviceSubType_Gamepad);
			lua_setfield(luaState, -2, "deviceSubTypeGamepad");
			lua_pushinteger(luaState, EXInputDeviceSubType_Wheel);
			lua_setfield(luaState, -2, "deviceSubTypeWheel");
			lua_pushinteger(luaState, EXInputDeviceSubType_ArcadeStick);
			lua_setfield(luaState, -2, "deviceSubTypeArcadeStick");
			lua_pushinteger(luaState, EXInputDeviceSubType_FlightStick);
			lua_setfield(luaState, -2, "deviceSubTypeFlightStick");
			lua_pushinteger(luaState, EXInputDeviceSubType_DancePad);
			lua_setfield(luaState, -2, "deviceSubTypeDancePad");
			lua_pushinteger(luaState, EXInputDeviceSubType_Guitar);
			lua_setfield(luaState, -2, "deviceSubTypeGuitar");
			lua_pushinteger(luaState, EXInputDeviceSubType_GuitarAlternate);
			lua_setfield(luaState, -2, "deviceSubTypeGuitarAlternate");
			lua_pushinteger(luaState, EXInputDeviceSubType_GuitarBass);
			lua_setfield(luaState, -2, "deviceSubTypeGuitarBass");
			lua_pushinteger(luaState, EXInputDeviceSubType_DrumKit);
			lua_setfield(luaState, -2, "deviceSubTypeDrumKit");
			lua_pushinteger(luaState, EXInputDeviceSubType_ArcadePad);
			lua_setfield(luaState, -2, "deviceSubTypeArcadePad");
			lua_pushvalue(luaState, -1);
			lua_setglobal(luaState, "xinput");
		}
		if (libraries & ELuaModuleLibraries_Runtime)
		{
			lua_newtable(luaState);
			luaL_setfuncs(luaState, runtimeLibrary, 0);
			lua_pushvalue(luaState, -1);
			lua_setglobal(luaState, "runtime");
		}
		if (libraries & ELuaModuleLibraries_Event)
		{
			lua_newtable(luaState);
			luaL_setfuncs(luaState, eventLibrary, 0);
			lua_pushvalue(luaState, -1);
			lua_setglobal(luaState, "event");
		}
		if (isFile)
		{
			if (luaL_loadfile(luaState, source.c_str()))
			{
				cerr << lua_tostring(luaState, -1) << endl;
				Close();
			}
		}
		else
		{
			if (luaL_loadstring(luaState, source.c_str()))
			{
				cerr << lua_tostring(luaState, -1) << endl;
				Close();
			}
		}

	}
}

/// <summary>
/// Destructor
/// </summary>
LuaModule::~LuaModule()
{
	Close();
}

/// <summary>
/// Is module active
/// </summary>
/// <returns>"true" if active, otherwise "false"</returns>
bool LuaModule::IsActive()
{
	return (luaState != nullptr);
}

/// <summary>
/// Execute module
/// </summary>
void LuaModule::Execute()
{
	if (luaState)
	{
		if (lua_pcall(luaState, 0, LUA_MULTRET, 0))
		{
			cerr << lua_tostring(luaState, -1) << endl;
			Close();
		}
		if (exitSignal)
		{
			Close();
		}
	}
}

/// <summary>
/// Invoke event
/// </summary>
/// <param name="eventName">Event name</param>
void LuaModule::InvokeEvent(const string & eventName)
{
	if (luaState)
	{
		map<string, vector<int>>::iterator it(events.find(eventName));
		if (it != events.end())
		{
			for (int function : it->second)
			{
				lua_rawgeti(luaState, LUA_REGISTRYINDEX, function);
				if (lua_pcall(luaState, 0, LUA_MULTRET, 0))
				{
					cerr << lua_tostring(luaState, -1) << endl;
					Close();
					break;
				}
			}
		}
		if (exitSignal)
		{
			Close();
		}
	}
}

/// <summary>
/// Close module
/// </summary>
void LuaModule::Close()
{
	if (luaState)
	{
		lua_close(luaState);
		instances.erase(luaState);
		luaState = nullptr;
	}
}
