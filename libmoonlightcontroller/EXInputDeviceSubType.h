#ifndef __MOONLIGHT_CONTROLLER_E_XINPUT_DEVICE_SUBTYPE_H__
#	define __MOONLIGHT_CONTROLLER_E_XINPUT_DEVICE_SUBTYPE_H__

// Moonlight controller namespace
namespace MoonlightController
{
	// XInput device sub-type enumerator
	enum EXInputDeviceSubType
	{
		// Unkown
		EXInputDeviceSubType_Unknown = 0x0,

		// Gamepad
		EXInputDeviceSubType_Gamepad = 0x1,

		// Wheel
		EXInputDeviceSubType_Wheel = 0x2,

		// Arcade stick
		EXInputDeviceSubType_ArcadeStick = 0x3,

		// Flight stick
		EXInputDeviceSubType_FlightStick = 0x4,

		// Dance pad
		EXInputDeviceSubType_DancePad = 0x5,

		// Guitar
		EXInputDeviceSubType_Guitar = 0x6,

		// Guitar alternate
		EXInputDeviceSubType_GuitarAlternate = 0x7,

		// Guitar bass
		EXInputDeviceSubType_GuitarBass = 0xB,

		// Drum kit
		EXInputDeviceSubType_DrumKit = 0x8,

		// Arcade pad
		EXInputDeviceSubType_ArcadePad = 0x13
	};
}
#endif
