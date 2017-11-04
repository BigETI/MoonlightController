#ifndef __MOONLIGHT_CONTROLLER_XINPUT_KEYSTROKE_H__
#	define __MOONLIGHT_CONTROLLER_XINPUT_KEYSTROKE_H__
#	include <libmoonlightcontroller/EXInputVirtualKey.h>
#	include <libmoonlightcontroller/EXInputKeyboardStates.h>

// Moonlight controller namespace
namespace MoonlightController
{
	// XInput keystroke class
	class XInputKeystroke
	{
	public:

		// Virtual key
		EXInputVirtualKey virtualKey;

		// Unicode
		wchar_t unicode;

		// Keyboard states
		EXInputKeyboardStates keyboardStates;

		// User index
		int userIndex;

		// HID code
		unsigned char hidCode;

		// Default constructor
		XInputKeystroke();

		// Copy constructor
		XInputKeystroke(const XInputKeystroke & keystroke);

		// Default constructor
		XInputKeystroke(EXInputVirtualKey _virtualKey, wchar_t _unicode, EXInputKeyboardStates _keyboardStates, int _userIndex, unsigned char _hidCode);

		// Assign operator
		XInputKeystroke & operator = (const XInputKeystroke & keystroke);
	};
}
#endif
