#define MOONLIGHT_CONTROLLER_LIBRARY
#include <libmoonlightcontroller/XInputCapabilities.h>

using namespace MoonlightController;

/// <summary>
/// Default constructor
/// </summary>
XInputCapabilities::XInputCapabilities() : deviceType(EXInputDeviceType_Gamepad), deviceSubType(EXInputDeviceSubType_Gamepad), deviceFeatures(static_cast<EXInputDeviceFeatures>(0)), buttons(static_cast<EXInputButtons>(0)), leftTrigger(0.0f), rightTrigger(0.0f), thumbLX(0.0f), thumbLY(0.0f), thumbRX(0.0f), thumbRY(0.0f), leftMotor(0.0f), rightMotor(0.0f)
{
	//
}

/// <summary>
/// Copy constructor
/// </summary>
/// <param name="capabilities">Capabilities</param>
XInputCapabilities::XInputCapabilities(const XInputCapabilities & capabilities) : deviceType(capabilities.deviceType), deviceSubType(capabilities.deviceSubType), deviceFeatures(capabilities.deviceFeatures), buttons(capabilities.buttons), leftTrigger(capabilities.leftTrigger), rightTrigger(capabilities.rightTrigger), thumbLX(capabilities.thumbLX), thumbLY(capabilities.thumbLY), thumbRX(capabilities.thumbRX), thumbRY(capabilities.thumbRY), leftMotor(capabilities.leftMotor), rightMotor(capabilities.rightMotor)
{
	//
}

/// <summary>
/// Constructor
/// </summary>
/// <param name="deviceType">Device type</param>
/// <param name="deviceSubType">Device sub-type</param>
/// <param name="deviceFeatures">Device feature</param>
/// <param name="buttons">Buttons</param>
/// <param name="leftTrigger">Left trigger</param>
/// <param name="rightTrigger">Right trigger</param>
/// <param name="thumbLX">THumb LX</param>
/// <param name="thumbLY">Thumb LY</param>
/// <param name="thumbRX">Thumb RX</param>
/// <param name="thumbRY">Thumb RY</param>
/// <param name="leftMotor">Left motor</param>
/// <param name="rightMotor">Right motor</param>
XInputCapabilities::XInputCapabilities(EXInputDeviceType _deviceType, EXInputDeviceSubType _deviceSubType, EXInputDeviceFeatures _deviceFeatures, EXInputButtons _buttons, float _leftTrigger, float _rightTrigger, float _thumbLX, float _thumbLY, float _thumbRX, float _thumbRY, float _leftMotor, float _rightMotor) : deviceType(_deviceType), deviceSubType(_deviceSubType), deviceFeatures(_deviceFeatures), buttons(_buttons), leftTrigger(_leftTrigger), rightTrigger(_rightTrigger), thumbLX(_thumbLX), thumbLY(_thumbLY), thumbRX(_thumbRX), thumbRY(_thumbRY), leftMotor(_leftMotor), rightMotor(_rightMotor)
{
	//
}

/// <summary>
/// Assign operator
/// </summary>
/// <param name="capabilities">XInput Capabilities</param>
/// <returns>This</returns>
XInputCapabilities & MoonlightController::XInputCapabilities::operator=(const XInputCapabilities & capabilities)
{
	deviceType = capabilities.deviceType;
	deviceSubType = capabilities.deviceSubType;
	deviceFeatures = capabilities.deviceFeatures;
	buttons = capabilities.buttons;
	leftTrigger = capabilities.leftTrigger;
	rightTrigger = capabilities.rightTrigger;
	thumbLX = capabilities.thumbLX;
	thumbLY = capabilities.thumbLY;
	thumbRX = capabilities.thumbRX;
	thumbRY = capabilities.thumbRY;
	leftMotor = capabilities.leftMotor;
	rightMotor = capabilities.rightMotor;
	return (*this);
}
