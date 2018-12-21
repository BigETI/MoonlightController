#define MOONLIGHT_CONTROLLER_LIBRARY

#include <libmoonlightcontroller/KeyboardController.h>
#include <libmoonlightcontroller/Platform.h>

using namespace MoonlightController;
using namespace std;

#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	include <linux/uinput.h>
#endif

/// <summary>
/// Default constructor
/// </summary>
KeyboardController::KeyboardController()
#if defined(MOONLIGHT_CONTROLLER_LINUX)
	: userInputOutput(EUserInputOutputType_Keyboard, "Moonlight controller (Keyboard)")
#endif
{
	//
}

/// <summary>
/// Destructor
/// </summary>
KeyboardController::~KeyboardController()
{
	//
}

/// <summary>
/// Click keyboard key
/// </summary>
/// <param name="key">Key code</param>
void KeyboardController::Click(int keyCode)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
	userInputOutput.write(EV_KEY, keyCode, 1);
	userInputOutput.write(EV_SYN, SYN_REPORT, 0);
	userInputOutput.write(EV_KEY, keyCode, 0);
	userInputOutput.write(EV_SYN, SYN_REPORT, 0);
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	INPUT in = { 0 };
	in.type = INPUT_KEYBOARD;
	in.ki.wVk = static_cast<WORD>(keyCode);
	in.ki.dwExtraInfo = GetMessageExtraInfo();
	SendInput(1, &in, sizeof(INPUT));
	in.ki.dwFlags = KEYEVENTF_KEYUP;
	in.ki.dwExtraInfo = GetMessageExtraInfo();
	SendInput(1, &in, sizeof(INPUT));
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
}

/// <summary>
/// Press keyboard key
/// </summary>
/// <param name="key">Key code</param>
/// <param name="down">Press down</param>
void KeyboardController::Press(int keyCode, bool down)
{
	if (down ? (!IsDown(keyCode)) : IsDown(keyCode))
	{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
		userInputOutput.write(EV_KEY, keyCode, down ? 1 : 0);
		userInputOutput.write(EV_SYN, SYN_REPORT, 0);
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
		INPUT in = { 0 };
		in.type = INPUT_KEYBOARD;
		in.ki.wVk = static_cast<WORD>(keyCode);
		if (!down)
		{
			in.ki.dwFlags = KEYEVENTF_KEYUP;
		}
		SendInput(1, &in, sizeof(INPUT));
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
		// TODO
#endif
	}
}

/// <summary>
/// Is keyboard key down
/// </summary>
/// <param name="keyCode">Key code</param>
/// <returns>"true" if keyboard key is down, otherwise "false"</returns>
bool KeyboardController::IsDown(int keyCode)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// TODO
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	return ((GetKeyState(keyCode) & 0x800) == 0x800);
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
}

/// <summary>
/// Text input
/// </summary>
/// <param name="input">Text input</param>
void KeyboardController::Input(const string & input)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// TODO
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	INPUT in = { 0 };
	in.type = INPUT_KEYBOARD;
	for (const char & c : input)
	{
		in.ki.wScan = c;
		in.ki.dwFlags = KEYEVENTF_UNICODE;
		in.ki.dwExtraInfo = GetMessageExtraInfo();
		SendInput(1, &in, sizeof(INPUT));
		in.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
		in.ki.dwExtraInfo = GetMessageExtraInfo();
		SendInput(1, &in, sizeof(INPUT));
	}
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
}
