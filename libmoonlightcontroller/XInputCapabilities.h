#ifndef __MOONLIGHT_CONTROLLER_XINPUT_CAPABILITIES_H__
#	define __MOONLIGHT_CONTROLLER_XINPUT_CAPABILITIES_H__

#	include <libmoonlightcontroller/EXInputDeviceType.h>
#	include <libmoonlightcontroller/EXInputDeviceSubType.h>
#	include <libmoonlightcontroller/EXInputDeviceFeatures.h>
#	include <libmoonlightcontroller/EXInputButtons.h>

// Moonlight controller namespace
namespace MoonlightController
{
	// XInput capabilities class
	class XInputCapabilities
	{
	public:

		// Device type
		EXInputDeviceType deviceType;

		// Device subtype
		EXInputDeviceSubType deviceSubType;

		// Device features
		EXInputDeviceFeatures deviceFeatures;

		// Buttons
		EXInputButtons buttons;

		// Left trigger
		float leftTrigger;

		// Right trigger
		float rightTrigger;

		// Thumb LX
		float thumbLX;

		// Thumb LY
		float thumbLY;

		// Thumb RX
		float thumbRX;

		// Thumb RY
		float thumbRY;

		// Left motor
		float leftMotor;

		// Right motor
		float rightMotor;

		// Default constructor
		XInputCapabilities();

		// Copy constructor
		XInputCapabilities(const XInputCapabilities & capabilities);

		// Constructor
		XInputCapabilities(EXInputDeviceType _deviceType, EXInputDeviceSubType _deviceSubType, EXInputDeviceFeatures _deviceFeatures, EXInputButtons _buttons, float _leftTrigger, float _rightTrigger, float _thumbLX, float _thumbLY, float _thumbRX, float _thumbRY, float _leftMotor, float _rightMotor);

		// Assign operator
		XInputCapabilities & operator = (const XInputCapabilities & capabilities);


	};
}
#endif
