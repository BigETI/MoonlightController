#ifndef __MOONLIGHT_CONTROLLER_E_XINPUT_DEVICE_SUB_TYPE_H__
#	define __MOONLIGHT_CONTROLLER_E_XINPUT_DEVICE_SUB_TYPE_H__

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// XInput device sub-type enumerator
	/// </summary>
	enum EXInputDeviceSubType
	{
		/// <summary>
		/// Unkown
		/// </summary>
		EXInputDeviceSubType_Unknown = 0x0,

		/// <summary>
		/// Gamepad
		/// </summary>
		EXInputDeviceSubType_Gamepad = 0x1,

		/// <summary>
		/// Wheel
		/// </summary>
		EXInputDeviceSubType_Wheel = 0x2,

		/// <summary>
		/// Arcade stick
		/// </summary>
		EXInputDeviceSubType_ArcadeStick = 0x3,

		/// <summary>
		/// Flight stick
		/// </summary>
		EXInputDeviceSubType_FlightStick = 0x4,

		/// <summary>
		/// Dance pad
		/// </summary>
		EXInputDeviceSubType_DancePad = 0x5,

		/// <summary>
		/// Guitar
		/// </summary>
		EXInputDeviceSubType_Guitar = 0x6,

		/// <summary>
		/// Guitar alternate
		/// </summary>
		EXInputDeviceSubType_GuitarAlternate = 0x7,

		/// <summary>
		/// Guitar bass
		/// </summary>
		EXInputDeviceSubType_GuitarBass = 0xB,

		/// <summary>
		/// Drum kit
		/// </summary>
		EXInputDeviceSubType_DrumKit = 0x8,

		/// <summary>
		/// Arcade pad
		/// </summary>
		EXInputDeviceSubType_ArcadePad = 0x13
	};
}
#endif
