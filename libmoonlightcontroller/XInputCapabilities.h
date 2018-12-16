#ifndef __MOONLIGHT_CONTROLLER_XINPUT_CAPABILITIES_H__
#	define __MOONLIGHT_CONTROLLER_XINPUT_CAPABILITIES_H__

#	include <libmoonlightcontroller/EXInputDeviceType.h>
#	include <libmoonlightcontroller/EXInputDeviceSubType.h>
#	include <libmoonlightcontroller/EXInputDeviceFeatures.h>
#	include <libmoonlightcontroller/EXInputButtons.h>

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// XInput capabilities class
	/// </summary>
	class XInputCapabilities
	{
	public:

		/// <summary>
		/// Device type
		/// </summary>
		EXInputDeviceType deviceType;

		/// <summary>
		/// Device subtype
		/// </summary>
		EXInputDeviceSubType deviceSubType;

		/// <summary>
		/// Device features
		/// </summary>
		EXInputDeviceFeatures deviceFeatures;

		/// <summary>
		/// Buttons
		/// </summary>
		EXInputButtons buttons;

		/// <summary>
		/// Left trigger
		/// </summary>
		float leftTrigger;

		/// <summary>
		/// Right trigger
		/// </summary>
		float rightTrigger;

		/// <summary>
		/// Thumb LX
		/// </summary>
		float thumbLX;

		/// <summary>
		/// Thumb LY
		/// </summary>
		float thumbLY;

		/// <summary>
		/// Thumb RX
		/// </summary>
		float thumbRX;

		/// <summary>
		/// Thumb RY
		/// </summary>
		float thumbRY;

		/// <summary>
		/// Left motor
		/// </summary>
		float leftMotor;

		/// <summary>
		/// Right motor
		/// </summary>
		float rightMotor;

		/// <summary>
		/// Default constructor
		/// </summary>
		XInputCapabilities();

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="capabilities">Capabilities</param>
		XInputCapabilities(const XInputCapabilities & capabilities);

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
		XInputCapabilities(EXInputDeviceType deviceType, EXInputDeviceSubType deviceSubType, EXInputDeviceFeatures deviceFeatures, EXInputButtons buttons, float leftTrigger, float rightTrigger, float thumbLX, float thumbLY, float thumbRX, float thumbRY, float leftMotor, float rightMotor);

		/// <summary>
		/// Assign operator
		/// </summary>
		/// <param name="capabilities">XInput Capabilities</param>
		/// <returns>This</returns>
		XInputCapabilities & operator = (const XInputCapabilities & capabilities);
	};
}
#endif
