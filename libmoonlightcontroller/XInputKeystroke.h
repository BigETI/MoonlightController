#ifndef __MOONLIGHT_CONTROLLER_XINPUT_KEYSTROKE_H__
#	define __MOONLIGHT_CONTROLLER_XINPUT_KEYSTROKE_H__

#	include <libmoonlightcontroller/EXInputVirtualKey.h>
#	include <libmoonlightcontroller/EXInputKeyboardStates.h>

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// XInput keystroke class
	/// </summary>
	class XInputKeystroke
	{
	public:

		/// <summary>
		/// Virtual key
		/// </summary>
		EXInputVirtualKey virtualKey;

		/// <summary>
		/// Unicode
		/// </summary>
		wchar_t unicode;

		/// <summary>
		/// Keyboard states
		/// </summary>
		EXInputKeyboardStates keyboardStates;

		/// <summary>
		/// User index
		/// </summary>
		int userIndex;

		/// <summary>
		/// HID code
		/// </summary>
		unsigned char hidCode;

		/// <summary>
		/// Default constructor
		/// </summary>
		XInputKeystroke();

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="keystroke">XInput keystroke</param>
		XInputKeystroke(const XInputKeystroke & keystroke);

		/// <summary>
		/// Default constructor
		/// </summary>
		/// <param name="virtualKey">Virtual key</param>
		/// <param name="unicode">Unicode</param>
		/// <param name="keyboardStates">Keyboard states</param>
		/// <param name="userIndex">User index</param>
		/// <param name="hidCode">HID code</param>
		XInputKeystroke(EXInputVirtualKey virtualKey, wchar_t unicode, EXInputKeyboardStates keyboardStates, int userIndex, unsigned char hidCode);

		/// <summary>
		/// Destructor
		/// </summary>
		~XInputKeystroke();

		/// <summary>
		/// Assign operator
		/// </summary>
		/// <param name="keystroke">XInput keystroke</param>
		/// <returns>This</returns>
		XInputKeystroke & operator = (const XInputKeystroke & keystroke);
	};
}
#endif
