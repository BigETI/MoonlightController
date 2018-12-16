#ifndef __MOONLIGHT_CONTROLLER_E_XINPUT_BATTERY_LEVEL_H__
#	define __MOONLIGHT_CONTROLLER_E_XINPUT_BATTERY_LEVEL_H__

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// XInput battery level enumerator
	/// </summary>
	enum EXInputBatteryLevel
	{
		/// <summary>
		/// Empty
		/// </summary>
		EXInputBatteryLevel_Empty = 0x0,

		/// <summary>
		/// Low
		/// </summary>
		EXInputBatteryLevel_Low = 0x1,

		/// <summary>
		/// Medium
		/// </summary>
		EXInputBatteryLevel_Medium = 0x2,

		/// <summary>
		/// Full
		/// </summary>
		EXInputBatteryLevel_Full = 0x3
	};
}
#endif
