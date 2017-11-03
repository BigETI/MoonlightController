#ifndef __MOONLIGHT_CONTROLLER_E_XINPUT_BUTTONS_H__
#	define __MOONLIGHT_CONTROLLER_E_XINPUT_BUTTONS_H__

// Moonlight controller namespace
namespace MoonlightController
{
	// XInput buttons namespace
	enum EXInputButtons
	{
		// D-Pad up
		EXInputButton_DPadUp = 0x1,

		// D-Pad down
		EXInputButton_DPadDown = 0x2,

		// D-Pad left
		EXInputButton_DPadLeft = 0x4,

		// D-Pad right
		EXInputButton_DPadRight = 0x8,

		// Start
		EXInputButton_Start = 0x10,

		// Back
		EXInputButton_Back = 0x20,

		// Left thumb
		EXInputButton_LeftThumb = 0x40,

		// Right thumb
		EXInputButton_RightThumb = 0x80,

		// Left shoulder
		EXInputButton_LeftShoulder = 0x100,

		// Right shoulder
		EXInputButton_RightShoulder = 0x200,

		// A
		EXInputButton_A = 0x1000,

		// B
		EXInputButton_B = 0x2000,

		// X
		EXInputButton_X = 0x4000,

		// Y
		EXInputButton_Y = 0x8000
	};
}
#endif