#define MOONLIGHT_CONTROLLER_LIBRARY
#include <libmoonlightcontroller/XInputKeystroke.h>

using namespace MoonlightController;

/// <summary>
/// Default constructor
/// </summary>
XInputKeystroke::XInputKeystroke() : virtualKey(static_cast<EXInputVirtualKey>(0)), unicode(L'\0'), keyboardStates(static_cast<EXInputKeyboardStates>(0)), userIndex(0), hidCode(0)
{
	//
}

/// <summary>
/// Copy constructor
/// </summary>
/// <param name="keystroke">XInput keystroke</param>
XInputKeystroke::XInputKeystroke(const XInputKeystroke & keystroke) : virtualKey(keystroke.virtualKey), unicode(keystroke.unicode), keyboardStates(keystroke.keyboardStates), userIndex(keystroke.userIndex), hidCode(keystroke.hidCode)
{
	//
}

/// <summary>
/// Default constructor
/// </summary>
/// <param name="virtualKey">Virtual key</param>
/// <param name="unicode">Unicode</param>
/// <param name="keyboardStates">Keyboard states</param>
/// <param name="userIndex">User index</param>
/// <param name="hidCode">HID code</param>
XInputKeystroke::XInputKeystroke(EXInputVirtualKey virtualKey, wchar_t unicode, EXInputKeyboardStates keyboardStates, int userIndex, unsigned char hidCode) : virtualKey(virtualKey), unicode(unicode), keyboardStates(keyboardStates), userIndex(userIndex), hidCode(hidCode)
{
	//
}

/// <summary>
/// Assign operator
/// </summary>
/// <param name="keystroke">XInput keystroke</param>
/// <returns>This</returns>
XInputKeystroke & MoonlightController::XInputKeystroke::operator=(const XInputKeystroke & keystroke)
{
	virtualKey = keystroke.virtualKey;
	unicode = keystroke.unicode;
	keyboardStates = keystroke.keyboardStates;
	userIndex = keystroke.userIndex;
	hidCode = keystroke.hidCode;
	return (*this);
}
