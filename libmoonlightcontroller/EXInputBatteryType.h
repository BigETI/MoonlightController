#ifndef __MOONLIGHT_CONTROLLER_E_XINPUT_BATTERY_TYPE_H__
#	define __MOONLIGHT_CONTROLLER_E_XINPUT_BATTERY_TYPE_H__

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// XInput battery type enumerator
	/// </summary>
	enum EXInputBatteryType
	{
		/// <summary>
		/// Disconnected
		/// </summary>
		EXInputBatteryType_Disconnected = 0x0,

		/// <summary>
		/// Wired
		/// </summary>
		EXInputBatteryType_Wired = 0x1,

		/// <summary>
		/// Alkaline
		/// </summary>
		EXInputBatteryType_Alkaline = 0x2,

		/// <summary>
		/// Nickel metal hybrid
		/// </summary>
		EXInputBatteryType_NiMH = 0x3,

		/// <summary>
		/// Unknown
		/// </summary>
		EXInputBatteryType_Unknown = 0xFF
	};
}
#endif
