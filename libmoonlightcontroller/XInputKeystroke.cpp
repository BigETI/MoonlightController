#define MOONLIGHT_CONTROLLER_LIBRARY
#include <libmoonlightcontroller/XInputKeystroke.h>

using namespace MoonlightController;

XInputKeystroke::XInputKeystroke() : virtualKey(static_cast<EXInputVirtualKey>(0)), unicode(L'\0'), keyboardStates(static_cast<EXInputKeyboardStates>(0)), userIndex(0), hidCode(0)
{
	//
}

XInputKeystroke::XInputKeystroke(const XInputKeystroke & keystroke) : virtualKey(keystroke.virtualKey), unicode(keystroke.unicode), keyboardStates(keystroke.keyboardStates), userIndex(keystroke.userIndex), hidCode(keystroke.hidCode)
{
	//
}

XInputKeystroke::XInputKeystroke(EXInputVirtualKey _virtualKey, wchar_t _unicode, EXInputKeyboardStates _keyboardStates, int _userIndex, unsigned char _hidCode) : virtualKey(_virtualKey), unicode(_unicode), keyboardStates(_keyboardStates), userIndex(_userIndex), hidCode(_hidCode)
{
	//
}

XInputKeystroke & MoonlightController::XInputKeystroke::operator=(const XInputKeystroke & keystroke)
{
	virtualKey = keystroke.virtualKey;
	unicode = keystroke.unicode;
	keyboardStates = keystroke.keyboardStates;
	userIndex = keystroke.userIndex;
	hidCode = keystroke.hidCode;
	return (*this);
}
