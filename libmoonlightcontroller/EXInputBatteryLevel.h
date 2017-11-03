#ifndef __MOONLIGHT_CONTROLLER_E_XINPUT_BATTERY_LEVEL_H__
#	define __MOONLIGHT_CONTROLLER_E_XINPUT_BATTERY_LEVEL_H__

// Moonlight controller namespace
namespace MoonlightController
{
	// XInput battery level enumerator
	enum EXInputBatteryLevel
	{
		// Empty
		EXInputBatteryLevel_Empty = 0x0,

		// Low
		EXInputBatteryLevel_Low = 0x1,

		// Medium
		EXInputBatteryLevel_Medium = 0x2,

		// Full
		EXInputBatteryLevel_Full = 0x3
	};
}
#endif
