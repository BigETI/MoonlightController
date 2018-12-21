#ifndef __MOONLIGHT_CONTROLLER_XINPUT_BATTERY_INFORMATION_H__
#	define __MOONLIGHT_CONTROLLER_XINPUT_BATTERY_INFORMATION_H__

#	include <libmoonlightcontroller/EXInputBatteryType.h>
#	include <libmoonlightcontroller/EXInputBatteryLevel.h>

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// XInput battery information class
	/// </summary>
	class XInputBatteryInformation
	{
	public:

		/// <summary>
		/// Battery type
		/// </summary>
		EXInputBatteryType batteryType;

		/// <summary>
		/// Battery level
		/// </summary>
		EXInputBatteryLevel batteryLevel;

		/// <summary>
		/// Default constructor
		/// </summary>
		XInputBatteryInformation();

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="batteryInformation">Battery information</param>
		XInputBatteryInformation(const XInputBatteryInformation & batteryInformation);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="batteryType">Battery type</param>
		/// <param name="batteryLevel">Battery level</param>
		XInputBatteryInformation(EXInputBatteryType batteryType, EXInputBatteryLevel batteryLevel);

		/// <summary>
		/// Destructor
		/// </summary>
		~XInputBatteryInformation();

		/// <summary>
		/// Assign operator
		/// </summary>
		/// <param name="batteryInformation">Battery information</param>
		/// <returns>This</returns>
		XInputBatteryInformation & operator = (const XInputBatteryInformation & batteryInformation);
	};
}
#endif
