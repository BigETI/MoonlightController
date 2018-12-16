#ifndef __MOONLIGHT_CONTROLLER_E_XINPUT_KEYBOARD_STATE_H__
#	define __MOONLIGHT_CONTROLLER_E_XINPUT_KEYBOARD_STATE_H__

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// XInput keyboard states enumerator
	/// </summary>
	enum EXInputKeyboardStates
	{
		/// <summary>
		/// Key down
		/// </summary>
		EXInputKeyboardStates_KeyDown = 0x1,

		/// <summary>
		/// Key up
		/// </summary>
		EXInputKeyboardStates_KeyUp = 0x2,

		/// <summary>
		/// Repeat
		/// </summary>
		EXInputKeyboardStates_Repeat = 0x4
	};
}
#endif
