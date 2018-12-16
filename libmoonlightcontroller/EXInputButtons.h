#ifndef __MOONLIGHT_CONTROLLER_E_XINPUT_BUTTONS_H__
#	define __MOONLIGHT_CONTROLLER_E_XINPUT_BUTTONS_H__

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// XInput buttons enumerator
	/// </summary>
	enum EXInputButtons
	{
		/// <summary>
		/// D-Pad up
		/// </summary>
		EXInputButton_DPadUp = 0x1,

		/// <summary>
		/// D-Pad down
		/// </summary>
		EXInputButton_DPadDown = 0x2,

		/// <summary>
		/// D-Pad left
		/// </summary>
		EXInputButton_DPadLeft = 0x4,

		/// <summary>
		/// D-Pad right
		/// </summary>
		EXInputButton_DPadRight = 0x8,

		/// <summary>
		/// Start
		/// </summary>
		EXInputButton_Start = 0x10,

		/// <summary>
		/// Back
		/// </summary>
		EXInputButton_Back = 0x20,

		/// <summary>
		/// Left thumb
		/// </summary>
		EXInputButton_LeftThumb = 0x40,

		/// <summary>
		/// Right thumb
		/// </summary>
		EXInputButton_RightThumb = 0x80,

		/// <summary>
		/// Left shoulder
		/// </summary>
		EXInputButton_LeftShoulder = 0x100,

		/// <summary>
		/// Right shoulder
		/// </summary>
		EXInputButton_RightShoulder = 0x200,

		/// <summary>
		/// A
		/// </summary>
		EXInputButton_A = 0x1000,

		/// <summary>
		/// B
		/// </summary>
		EXInputButton_B = 0x2000,

		/// <summary>
		/// X
		/// </summary>
		EXInputButton_X = 0x4000,

		/// <summary>
		/// Y
		/// </summary>
		EXInputButton_Y = 0x8000
	};
}
#endif
