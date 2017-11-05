#ifndef __MOONLIGHT_CONTROLLER_XINPUT_CONTROLLER_H__
#	define __MOONLIGHT_CONTROLLER_XINPUT_CONTROLLER_H__

#	include <libmoonlightcontroller/EXInputButtons.h>
#	include <libmoonlightcontroller/EXInputAxis.h>
#	include <libmoonlightcontroller/XInputBatteryInformation.h>
#	include <libmoonlightcontroller/EXInputBatteryDeviceType.h>
#	include <libmoonlightcontroller/XInputCapabilities.h>
#	include <libmoonlightcontroller/XInputKeystroke.h>
#	include <libmoonlightcontroller/Platform.h>
#	include <string>

#	if defined(MOONLIGHT_CONTROLLER_LINUX)
#		include <libmoonlightcontroller/Linux/UserInputOutput.h>
#	endif

// Moonlight controller namespace
namespace MoonlightController
{
	// XInput controller class
	class XInputController
	{
	private:
		#if defined(MOONLIGHT_CONTROLLER_LINUX)
		
		// User input output
		UserInputOutput userInputOutput;

		#endif

		// Copy constructor
		XInputController(const XInputController &);

		// Assign operator
		XInputController & operator = (const XInputController &);

	public:

		// Default constructor
		XInputController();

		// Destructor
		~XInputController();

		// Is controller connected
		bool IsConnected(int controllerID);

		// Get controller buttons
		EXInputButtons GetButtons(int controllerID);

		// Get controller axis
		float GetAxis(int controllerID, EXInputAxis axis);

		// Set controller vibration
		void SetVibration(int controllerID, float leftMotor, float rightMotor);

		// Get controller audio device IDs
		void GetAudioDeviceIDs(int controllerID, std::wstring & renderDeviceID, std::wstring & captureDeviceID);

		// Get controller battery information
		XInputBatteryInformation GetBatteryInformation(int controllerID, EXInputBatteryDeviceType batteryDeviceType);

		// Get controller capabilities
		XInputCapabilities GetCapabilities(int controllerID);

		// Get controller keystroke
		XInputKeystroke GetKeystroke(int controllerID);
	};
}
#endif
