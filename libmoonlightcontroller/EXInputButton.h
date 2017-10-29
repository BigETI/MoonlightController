#ifndef __MOONLIGHT_CONTROLLER_E_XINPUT_BUTTON_H__
#	define __MOONLIGHT_CONTROLLER_E_XINPUT_BUTTON_H__
enum EXInputButton
{
	EXInputButton_DPadUp = 0x1,
	EXInputButton_DPadDown = 0x2,
	EXInputButton_DPadLeft = 0x4,
	EXInputButton_DPadRight = 0x8,
	EXInputButton_Start = 0x10,
	EXInputButton_Back = 0x20,
	EXInputButton_LeftThumb = 0x40,
	EXInputButton_RightThumb = 0x80,
	EXInputButton_LeftShoulder = 0x100,
	EXInputButton_RightShoulder = 0x200,
	EXInputButton_A = 0x1000,
	EXInputButton_B = 0x2000,
	EXInputButton_X = 0x4000,
	EXInputButton_Y = 0x8000
};
#endif