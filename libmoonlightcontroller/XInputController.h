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

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// XInput controller class
	/// </summary>
	class XInputController
	{
	private:
#if defined(MOONLIGHT_CONTROLLER_LINUX)

		/// <summary>
		/// User input output
		/// </summary>
		UserInputOutput userInputOutput;

#endif

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="">XInput controller</param>
		XInputController(const XInputController &);

		/// <summary>
		/// Assign operator
		/// </summary>
		/// <param name="">XInput controller</param>
		/// <returns>This</returns>
		XInputController & operator = (const XInputController &);

	public:

		/// <summary>
		/// Maximal controllers
		/// </summary>
		static const size_t MaxControllers;

		/// <summary>
		/// Default constructor
		/// </summary>
		XInputController();

		/// <summary>
		/// Destructor
		/// </summary>
		~XInputController();

		/// <summary>
		/// Is controller connected
		/// </summary>
		/// <param name="controllerID">Controller ID</param>
		/// <returns>"true" if connected, otherwise "false"</returns>
		bool IsConnected(int controllerID);

		/// <summary>
		/// Get controller buttons
		/// </summary>
		/// <param name="controllerID">Controller ID</param>
		/// <returns>Controller buttons</returns>
		EXInputButtons GetButtons(int controllerID);

		/// <summary>
		/// Get controller axis
		/// </summary>
		/// <param name="controllerID">Controller ID</param>
		/// <param name="axis">Axis</param>
		/// <returns>Axis value between -1.0 and 1.0</returns>
		float GetAxis(int controllerID, EXInputAxis axis);

		/// <summary>
		/// Set controller vibration
		/// </summary>
		/// <param name="controllerID">Controller ID</param>
		/// <param name="leftMotor">Left motor</param>
		/// <param name="rightMotor">Right motor</param>
		void SetVibration(int controllerID, float leftMotor, float rightMotor);

		/// <summary>
		/// Get controller audio device IDs
		/// </summary>
		/// <param name="controllerID">Controller ID</param>
		/// <param name="renderDeviceID">Render device ID</param>
		/// <param name="captureDeviceID">Capture device ID</param>
		void GetAudioDeviceIDs(int controllerID, std::wstring & renderDeviceID, std::wstring & captureDeviceID);

		/// <summary>
		/// Get controller battery information
		/// </summary>
		/// <param name="controllerID">Controller ID</param>
		/// <param name="batteryDeviceType">Battery device type</param>
		/// <param name="batteryInformation">Battery information</param>
		/// <returns>Battery information</returns>
		XInputBatteryInformation & GetBatteryInformation(int controllerID, EXInputBatteryDeviceType batteryDeviceType, XInputBatteryInformation & batteryInformation);

		/// <summary>
		/// Get controller XInput capabilities
		/// </summary>
		/// <param name="controllerID">Controller ID</param>
		/// <param name="capabilties">Controller XInput capabilities</param>
		/// <returns>Controller XInput capabilities</returns>
		XInputCapabilities & GetCapabilities(int controllerID, XInputCapabilities & capabilties);

		/// <summary>
		/// Get controller keystroke
		/// </summary>
		/// <param name="controllerID">Controller ID</param>
		/// <param name="keystroke">Controller keystroke</param>
		/// <returns>Controller keystroke</returns>
		XInputKeystroke & GetKeystroke(int controllerID, XInputKeystroke & keystroke);
	};
}
#endif
