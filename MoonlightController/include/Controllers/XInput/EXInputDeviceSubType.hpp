#pragma once

namespace MoonlightController::Controllers::XInput {

	/// <summary>
	/// XInput device sub-type enumerator
	/// </summary>
	enum class EXInputDeviceSubType {

		/// <summary>
		/// Unkown
		/// </summary>
		Unknown = 0x0,

		/// <summary>
		/// Gamepad
		/// </summary>
		Gamepad = 0x1,

		/// <summary>
		/// Wheel
		/// </summary>
		Wheel = 0x2,

		/// <summary>
		/// Arcade stick
		/// </summary>
		ArcadeStick = 0x3,

		/// <summary>
		/// Flight stick
		/// </summary>
		FlightStick = 0x4,

		/// <summary>
		/// Dance pad
		/// </summary>
		DancePad = 0x5,

		/// <summary>
		/// Guitar
		/// </summary>
		Guitar = 0x6,

		/// <summary>
		/// Guitar alternate
		/// </summary>
		GuitarAlternate = 0x7,

		/// <summary>
		/// Guitar bass
		/// </summary>
		GuitarBass = 0xB,

		/// <summary>
		/// Drum kit
		/// </summary>
		DrumKit = 0x8,

		/// <summary>
		/// Arcade pad
		/// </summary>
		ArcadePad = 0x13
	};
}
