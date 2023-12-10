#include <Controllers/XInput/XInputCapabilities.hpp>

using namespace MoonlightController::Controllers::XInput;

XInputCapabilities::XInputCapabilities() :
	deviceType(EXInputDeviceType::Gamepad),
	deviceSubType(EXInputDeviceSubType::Gamepad),
	deviceFeatures(static_cast<EXInputDeviceFeatures>(0)),
	buttons(static_cast<EXInputButtons>(0)),
	leftTrigger(0.0f),
	rightTrigger(0.0f),
	thumbLX(0.0f),
	thumbLY(0.0f),
	thumbRX(0.0f),
	thumbRY(0.0f),
	leftMotor(0.0f),
	rightMotor(0.0f) {
	// ...
}

XInputCapabilities::XInputCapabilities(
	EXInputDeviceType deviceType,
	EXInputDeviceSubType deviceSubType,
	EXInputDeviceFeatures deviceFeatures,
	EXInputButtons buttons,
	float leftTrigger,
	float rightTrigger,
	float thumbLX,
	float thumbLY,
	float thumbRX,
	float thumbRY,
	float leftMotor,
	float rightMotor
) :
	deviceType(deviceType),
	deviceSubType(deviceSubType),
	deviceFeatures(deviceFeatures),
	buttons(buttons),
	leftTrigger(leftTrigger),
	rightTrigger(rightTrigger),
	thumbLX(thumbLX),
	thumbLY(thumbLY),
	thumbRX(thumbRX),
	thumbRY(thumbRY),
	leftMotor(leftMotor),
	rightMotor(rightMotor) {
	//
}
