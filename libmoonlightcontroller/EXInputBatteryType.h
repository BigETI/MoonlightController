#ifndef __MOONLIGHT_CONTROLLER_E_XINPUT_BATTERY_TYPE_H__
#	define __MOONLIGHT_CONTROLLER_E_XINPUT_BATTERY_TYPE_H__

// Moonlight controller namespace
namespace MoonlightController
{
	// XInput battery type enumerator
	enum EXInputBatteryType
	{
		// Disconnected
		EXInputBatteryType_Disconnected = 0x0,

		// Wired
		EXInputBatteryType_Wired = 0x1,

		// Alkaline
		EXInputBatteryType_Alkaline = 0x2,

		// Nickel metal hybrid
		EXInputBatteryType_NiMH = 0x3,

		// Unknown
		EXInputBatteryType_Unknown = 0xFF
	};
}
#endif
