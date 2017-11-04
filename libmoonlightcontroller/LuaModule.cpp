#define MOONLIGHT_CONTROLLER_LIBRARY
#include <iostream>
#include <locale>
#include <codecvt>
#include <libmoonlightcontroller/LuaModule.h>
#include <libmoonlightcontroller/MouseController.h>
#include <libmoonlightcontroller/KeyboardController.h>
#include <libmoonlightcontroller/XInputController.h>

using namespace MoonlightController;
using namespace std;

static LuaModule *instance(nullptr);

static wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

// Lua mouse.setPosition
static int mouse_setPosition(lua_State *luaState)
{
	if (lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2))
	{
		MouseController::SetPosition(static_cast<int>(lua_tointeger(luaState, 1)), static_cast<int>(lua_tointeger(luaState, 2)));
	}
	return 0;
}

// Lua mouse.getPosition()
int mouse_getPosition(lua_State *luaState)
{
	Position position(MouseController::GetPosition());
	lua_pushinteger(luaState, position.x);
	lua_pushinteger(luaState, position.y);
	return 2;
}

// Lua mouse.move
static int mouse_move(lua_State *luaState)
{
	if (lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2))
	{
		MouseController::Move(static_cast<int>(lua_tointeger(luaState, 1)), static_cast<int>(lua_tointeger(luaState, 2)));
	}
	return 0;
}

// Lua mouse.click
int mouse_click(lua_State *luaState)
{
	if (lua_isinteger(luaState, 1))
	{
		MouseController::Click(static_cast<EMouseButton>(static_cast<int>(lua_tointeger(luaState, 1))));
	}
	return 0;
}

// Lua mouse.press
int mouse_press(lua_State *luaState)
{
	if (lua_isinteger(luaState, 1) && lua_isboolean(luaState, 2))
	{
		MouseController::Press(static_cast<EMouseButton>(static_cast<int>(lua_tointeger(luaState, 1))), lua_toboolean(luaState, 2));
	}
	return 0;
}

// mouse.isDown
int mouse_isDown(lua_State *luaState)
{
	int ret(0);
	if (lua_isinteger(luaState, 1))
	{
		lua_pushboolean(luaState, MouseController::IsDown(static_cast<EMouseButton>(lua_tointeger(luaState, 1))));
		ret = 1;
	}
	return ret;
}

// mouse.scroll
int mouse_scroll(lua_State *luaState)
{
	if (lua_isinteger(luaState, 1))
	{
		MouseController::Scroll(static_cast<int>(lua_tointeger(luaState, 1)));
	}
	return 0;
}

// Lua keyboard.click
int keyboard_click(lua_State *luaState)
{
	if (lua_isinteger(luaState, 1))
	{
		KeyboardController::Click(static_cast<int>(lua_tointeger(luaState, 1)));
	}
	return 0;
}

// Lua keyboard.press
int keyboard_press(lua_State *luaState)
{
	if (lua_isinteger(luaState, 1) && lua_isboolean(luaState, 2))
	{
		KeyboardController::Press(static_cast<int>(lua_tointeger(luaState, 1)), lua_toboolean(luaState, 2));
	}
	return 0;
}

// Lua keyboard.input
int keyboard_input(lua_State *luaState)
{
	if (lua_isstring(luaState, 1))
	{
		KeyboardController::Input(lua_tostring(luaState, 1));
	}
	return 0;
}

// Lua xinput.isConnected
int xinput_isConnected(lua_State *luaState)
{
	int ret(0);
	if (lua_isinteger(luaState, 1))
	{
		lua_pushboolean(luaState, XInputController::IsConnected(static_cast<int>(lua_tointeger(luaState, 1)) - 1));
		ret = 1;
	}
	return ret;
}

// Lua xinput.getButtons
int xinput_getButtons(lua_State *luaState)
{
	int ret(0);
	if (lua_isinteger(luaState, 1))
	{
		lua_pushinteger(luaState, XInputController::GetButtons(static_cast<int>(lua_tointeger(luaState, 1)) - 1));
		ret = 1;
	}
	return ret;
}

// Lua xinput.getAxis
int xinput_getAxis(lua_State *luaState)
{
	int ret(0);
	if (lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2))
	{
		lua_pushnumber(luaState, XInputController::GetAxis(static_cast<int>(lua_tointeger(luaState, 1)) - 1, static_cast<EXInputAxis>(lua_tointeger(luaState, 2))));
		ret = 1;
	}
	return ret;
}

// Lua xinput.setVibration
int xinput_setVibration(lua_State *luaState)
{
	if (lua_isinteger(luaState, 1) && lua_isnumber(luaState, 2) && lua_isnumber(luaState, 3))
	{
		XInputController::SetVibration(static_cast<int>(lua_tointeger(luaState, 1)) - 1, static_cast<float>(lua_tonumber(luaState, 2)), static_cast<float>(lua_tonumber(luaState, 3)));
	}
	return 0;
}

// Lua xinput.getAudioDeviceIDs
int xinput_getAudioDeviceIDs(lua_State *luaState)
{
	int ret(0);
	if (lua_isinteger(luaState, 1))
	{
		wstring render_device_id;
		wstring capture_device_id;
		XInputController::GetAudioDeviceIDs(static_cast<int>(lua_tointeger(luaState, 1)) - 1, render_device_id, capture_device_id);
		lua_pushstring(luaState, converter.to_bytes(render_device_id).c_str());
		lua_pushstring(luaState, converter.to_bytes(capture_device_id).c_str());
		ret = 2;
	}
	return ret;
}

// Lua xinput.getBatteryInformation
int xinput_getBatteryInformation(lua_State *luaState)
{
	int ret(0);
	if (lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2))
	{
		XInputBatteryInformation batteryInformation(XInputController::GetBatteryInformation(static_cast<int>(lua_tointeger(luaState, 1)) - 1, static_cast<EXInputBatteryDeviceType>(lua_tointeger(luaState, 2))));
		lua_pushinteger(luaState, static_cast<int>(batteryInformation.batteryType));
		lua_pushinteger(luaState, static_cast<int>(batteryInformation.batteryLevel));
		ret = 2;
	}
	return ret;
}

// Lua xinput.getCapabilities
int xinput_getCapabilities(lua_State *luaState)
{
	int ret(0);
	if (lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2))
	{
		XInputCapabilities capabilities(XInputController::GetCapabilities(static_cast<int>(lua_tointeger(luaState, 1)) - 1));
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

// Lua xinput.getKeystroke
int xinput_getKeystroke(lua_State *luaState)
{
	int ret(0);
	if (lua_isinteger(luaState, 1) && lua_isinteger(luaState, 2))
	{
		XInputKeystroke keystroke(XInputController::GetKeystroke(static_cast<int>(lua_tointeger(luaState, 1)) - 1));
		lua_pushinteger(luaState, static_cast<int>(keystroke.virtualKey));
		lua_pushinteger(luaState, static_cast<int>(keystroke.unicode));
		lua_pushinteger(luaState, static_cast<int>(keystroke.keyboardStates));
		lua_pushinteger(luaState, keystroke.userIndex);
		lua_pushinteger(luaState, keystroke.hidCode);
		ret = 5;
	}
	return ret;
}

// Lua runtime.exit
int runtime_exit(lua_State *luaState)
{
	if (instance)
	{
		instance->SetExitSignal();
	}
	return 0;
}

// Lua event.register
int event_register(lua_State *luaState)
{
	if (lua_isstring(luaState, 1) && lua_isfunction(luaState, 2))
	{
		string name = lua_tostring(luaState, 1);
		int func = luaL_ref(luaState, LUA_REGISTRYINDEX);
		map<string, vector<int>>::iterator it(instance->events.find(name));
		if (it == instance->events.end())
		{
			instance->events.insert(pair<string, vector<int>>(name, { func }));
		}
		else
		{
			instance->events[name].push_back(func);
		}
	}
	return 0;
}

// Mouse library
static const luaL_Reg mouseLibrary[] = {
	{ "setPosition", mouse_setPosition },
	{ "getPosition", mouse_getPosition },
	{ "move", mouse_move },
	{ "click", mouse_click },
	{ "press", mouse_press },
	{ "isDown", mouse_isDown },
	{ "scroll", mouse_scroll },
	{ nullptr, nullptr }
};

// Keyboard library
static const luaL_Reg keyboardLibrary[] =
{
	{ "click", keyboard_click },
	{ "press", keyboard_press },
	{ "input", keyboard_input },
	{ nullptr, nullptr }
};

// XInput library
static const luaL_Reg xInputLibrary[] =
{
	{ "isConnected", xinput_isConnected },
	{ "getButtons", xinput_getButtons },
	{ "getAxis", xinput_getAxis },
	{ "setVibration", xinput_setVibration },
	{ "getAudioDeviceIDs", xinput_getAudioDeviceIDs },
	{ "getBatteryInformation", xinput_getBatteryInformation },
	{ "getCapabilities", xinput_getCapabilities },
	{ "getKeystroke", xinput_getKeystroke },
	{ nullptr, nullptr }
};

// Runtime library
static const luaL_Reg runtimeLibrary[] =
{
	{ "exit", runtime_exit },
	{ nullptr, nullptr }
};

// Event library
static const luaL_Reg eventLibrary[] =
{
	{ "register", event_register },
	{ nullptr, nullptr }
};

void LuaModule::SetExitSignal()
{
	exitSignal = true;
}

LuaModule::LuaModule(string _source, bool _isFile, ELuaModuleLibraries libraries) : source(_source), isFile(_isFile), luaState(nullptr), exitSignal(false)
{
	luaState = luaL_newstate();
	if (luaState)
	{
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

LuaModule::~LuaModule()
{
	Close();
}

bool LuaModule::IsActive()
{
	return (luaState != nullptr);
}

void LuaModule::Execute()
{
	if (luaState)
	{
		instance = this;
		if (lua_pcall(luaState, 0, LUA_MULTRET, 0))
		{
			cerr << lua_tostring(luaState, -1) << endl;
			Close();
		}
		if (exitSignal)
		{
			Close();
		}
		instance = nullptr;
	}
}

void LuaModule::InvokeEvent(string eventName)
{
	if (luaState)
	{
		instance = this;
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
		instance = nullptr;
	}
}

void LuaModule::Close()
{
	if (luaState)
	{
		lua_close(luaState);
		luaState = nullptr;
	}
}