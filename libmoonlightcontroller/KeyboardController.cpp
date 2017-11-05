#define MOONLIGHT_CONTROLLER_LIBRARY

#include <libmoonlightcontroller/KeyboardController.h>
#include <libmoonlightcontroller/Platform.h>
#include <set>

using namespace MoonlightController;
using namespace std;

#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	include <linux/uinput.h>
#endif

static set<int> isDown;

KeyboardController::KeyboardController()
#if defined(MOONLIGHT_CONTROLLER_LINUX)
	: userInputOutput(EUserInputOutputType_Keyboard, "Moonlight controller (Keyboard)")
#endif
{
	//
}

KeyboardController::~KeyboardController()
{
	//
}

void KeyboardController::Click(int key)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
	userInputOutput.write(EV_KEY, key, 1);
	userInputOutput.write(EV_SYN, SYN_REPORT, 0);
	userInputOutput.write(EV_KEY, key, 0);
	userInputOutput.write(EV_SYN, SYN_REPORT, 0);
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	INPUT in;
	memset(&in, 0, sizeof(INPUT));
	in.type = INPUT_KEYBOARD;
	in.ki.wVk = static_cast<WORD>(key);
	in.ki.dwExtraInfo = GetMessageExtraInfo();
	SendInput(1, &in, sizeof(INPUT));
	in.ki.dwFlags = KEYEVENTF_KEYUP;
	in.ki.dwExtraInfo = GetMessageExtraInfo();
	SendInput(1, &in, sizeof(INPUT));
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// To-do
#endif
}

void KeyboardController::Press(int key, bool down)
{
	if (down ? (!IsDown(key)) : IsDown(key))
	{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
		userInputOutput.write(EV_KEY, key, down ? 1 : 0);
		userInputOutput.write(EV_SYN, SYN_REPORT, 0);
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
		INPUT in;
		memset(&in, 0, sizeof(INPUT));
		in.type = INPUT_KEYBOARD;
		in.ki.wVk = static_cast<WORD>(key);
		if (!down)
		{
			in.ki.dwFlags = KEYEVENTF_KEYUP;
		}
		SendInput(1, &in, sizeof(INPUT));
		
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
		// To-do
#endif
		if (down)
		{
			isDown.insert(key);
		}
		else
		{
			isDown.erase(isDown.find(key));
		}
	}
}

bool MoonlightController::KeyboardController::IsDown(int key)
{
	return (isDown.find(key) != isDown.end());
}

void KeyboardController::Input(string input)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	INPUT in;
	memset(&in, 0, sizeof(INPUT));
	in.type = INPUT_KEYBOARD;
	for (char c : input)
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
	// To-do
#endif
	}
