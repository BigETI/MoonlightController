#ifndef __MOONLIGHT_CONTROLLER_XINPUT_CONTROLLER_H__
#	define __MOONLIGHT_CONTROLLER_XINPUT_CONTROLLER_H__
#	include <libmoonlightcontroller/EXInputButtons.h>
#	include <libmoonlightcontroller/EXInputAxis.h>
#	include <libmoonlightcontroller/XInputBatteryInformation.h>
#	include <libmoonlightcontroller/EXInputBatteryDeviceType.h>
#	include <libmoonlightcontroller/XInputCapabilities.h>
#	include <libmoonlightcontroller/XInputKeystroke.h>
#	include <string>

// Moonlight controller namespace
namespace MoonlightController
{
	// XInput controller class
	class XInputController
	{
	private:
		// Default constructor
		XInputController();

		// Copy constructor
		XInputController(const XInputController &);

		// Assign operator
		XInputController & operator = (const XInputController &);
	public:
		// Is controller connected
		static bool IsConnected(int controllerID);

		// Get controller buttons
		static EXInputButtons GetButtons(int controllerID);

		// Get controller axis
		static float GetAxis(int controllerID, EXInputAxis axis);

		// Set controller vibration
		static void SetVibration(int controllerID, float leftMotor, float rightMotor);

		// Get controller audio device IDs
		static void GetAudioDeviceIDs(int controllerID, std::wstring & renderDeviceID, std::wstring & captureDeviceID);

		// Get controller battery information
		static XInputBatteryInformation GetBatteryInformation(int controllerID, EXInputBatteryDeviceType batteryDeviceType);

		// Get controller capabilities
		static XInputCapabilities GetCapabilities(int controllerID);

		// Get controller keystroke
		static XInputKeystroke GetKeystroke(int controllerID);
	};
}
#endif
