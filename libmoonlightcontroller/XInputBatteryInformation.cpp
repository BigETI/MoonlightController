#define MOONLIGHT_CONTROLLER_LIBRARY
#include <libmoonlightcontroller/XInputBatteryInformation.h>

using namespace MoonlightController;

/// <summary>
/// Default constructor
/// </summary>
XInputBatteryInformation::XInputBatteryInformation() : batteryType(EXInputBatteryType_Unknown), batteryLevel(EXInputBatteryLevel_Empty)
{
	//
}

/// <summary>
/// Copy constructor
/// </summary>
/// <param name="batteryInformation">Battery information</param>
XInputBatteryInformation::XInputBatteryInformation(const XInputBatteryInformation & batteryInformation) : batteryType(batteryInformation.batteryType), batteryLevel(batteryInformation.batteryLevel)
{
	//
}

/// <summary>
/// Constructor
/// </summary>
/// <param name="batteryType">Battery type</param>
/// <param name="batteryLevel">Battery level</param>
XInputBatteryInformation::XInputBatteryInformation(EXInputBatteryType batteryType, EXInputBatteryLevel batteryLevel) : batteryType(batteryType), batteryLevel(batteryLevel)
{
	//
}

/// <summary>
/// Destructor
/// </summary>
XInputBatteryInformation::~XInputBatteryInformation()
{
	//
}

/// <summary>
/// Assign operator
/// </summary>
/// <param name="batteryInformation">Battery information</param>
/// <returns>This</returns>
XInputBatteryInformation & XInputBatteryInformation::operator = (const XInputBatteryInformation & batteryInformation)
{
	batteryType = batteryInformation.batteryType;
	batteryLevel = batteryInformation.batteryLevel;
	return (*this);
}
