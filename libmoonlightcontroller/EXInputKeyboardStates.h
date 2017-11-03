#ifndef __MOONLIGHT_CONTROLLER_E_XINPUT_KEYBOARD_STATE_H__
#	define __MOONLIGHT_CONTROLLER_E_XINPUT_KEYBOARD_STATE_H__

// Moonlight controller namespace
namespace MoonlightController
{
	// XInput keyboard states enumerator
	enum EXInputKeyboardStates
	{
		// Key down
		EXInputKeyboardStates_KeyDown = 0x1,

		// Key up
		EXInputKeyboardStates_KeyUp = 0x2,

		// Repeat
		EXInputKeyboardStates_Repeat = 0x4
	};
}
#endif
