#define MOONLIGHT_CONTROLLER_LIBRARY
#include <XInputBatteryInformation.h>

using namespace MoonlightController;

XInputBatteryInformation::XInputBatteryInformation() : batteryType(EXInputBatteryType_Unknown), batteryLevel(EXInputBatteryLevel_Empty)
{
	//
}

XInputBatteryInformation::XInputBatteryInformation(const XInputBatteryInformation & batteryInformation) : batteryType(batteryInformation.batteryType), batteryLevel(batteryInformation.batteryLevel)
{
	//
}

XInputBatteryInformation::XInputBatteryInformation(EXInputBatteryType _batteryType, EXInputBatteryLevel _batteryLevel) : batteryType(_batteryType), batteryLevel(_batteryLevel)
{
	//
}

XInputBatteryInformation & XInputBatteryInformation::operator = (const XInputBatteryInformation & batteryInformation)
{
	batteryType = batteryInformation.batteryType;
	batteryLevel = batteryInformation.batteryLevel;
	return (*this);
}
