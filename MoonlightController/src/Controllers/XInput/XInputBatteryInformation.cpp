#include <Controllers/XInput/EXInputBatteryLevel.hpp>
#include <Controllers/XInput/EXInputBatteryType.hpp>
#include <Controllers/XInput/XInputBatteryInformation.hpp>

using namespace MoonlightController::Controllers::XInput;

XInputBatteryInformation::XInputBatteryInformation() : batteryType(EXInputBatteryType::Unknown), batteryLevel(EXInputBatteryLevel::Empty) {
	// ...
}
XInputBatteryInformation::XInputBatteryInformation(EXInputBatteryType batteryType, EXInputBatteryLevel batteryLevel) : batteryType(batteryType), batteryLevel(batteryLevel) {
	//
}
