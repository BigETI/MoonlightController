#ifndef __MOONLIGHT_CONTROLLER_XINPUT_CONTROLLER_H__
#	define __MOONLIGHT_CONTROLLER_XINPUT_CONTROLLER_H__
#	include <EXInputButton.h>
#	include <EXInputAxis.h>
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
		// Is gamepad connected
		static bool IsConnected(int controllerID);

		// Get gamepad buttons
		static EXInputButton GetButtons(int controllerID);

		// Get gamepad axis
		static float GetAxis(int controllerID, EXInputAxis axis);

		// Set gamepad vibration
		static void SetVibration(int controllerID, float leftMotor, float rightMotor);
	};
}
#endif
