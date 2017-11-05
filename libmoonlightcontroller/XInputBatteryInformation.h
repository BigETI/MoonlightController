#ifndef __MOONLIGHT_CONTROLLER_XINPUT_BATTERY_INFORMATION_H__
#	define __MOONLIGHT_CONTROLLER_XINPUT_BATTERY_INFORMATION_H__

#	include <libmoonlightcontroller/EXInputBatteryType.h>
#	include <libmoonlightcontroller/EXInputBatteryLevel.h>

// Moonlight controller namespace
namespace MoonlightController
{
	// XInput battery information class
	class XInputBatteryInformation
	{
	public:

		// Battery type
		EXInputBatteryType batteryType;

		// Battery level
		EXInputBatteryLevel batteryLevel;

		// Default constructor
		XInputBatteryInformation();

		// Copy constructor
		XInputBatteryInformation(const XInputBatteryInformation & batteryInformation);

		// Constructor
		XInputBatteryInformation(EXInputBatteryType _batteryType, EXInputBatteryLevel _batteryLevel);

		// Assign operator
		XInputBatteryInformation & operator = (const XInputBatteryInformation &);
	};
}
#endif
