#define MOONLIGHT_CONTROLLER_LIBRARY
#include <libmoonlightcontroller/XInputController.h>
#include <libmoonlightcontroller/Platform.h>
#if defined(MOONLIGHT_CONTROLLER_LINUX)

#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
#include <Xinput.h>
#elif defined(MOONLIGHT_CONTROLLER_OSX)

#endif

using namespace MoonlightController;
using namespace std;

/// <summary>
/// Maximal controllers
/// </summary>
const size_t XInputController::MaxControllers(XUSER_MAX_COUNT);

/// <summary>
/// Default constructor
/// </summary>
XInputController::XInputController()
#if defined(MOONLIGHT_CONTROLLER_LINUX)
	: userInputOutput(EUserInputOutputType_Gamepad, "Moonlight controller (Gamepad)")
#endif
{
	//
}

/// <summary>
/// Destructor
/// </summary>
XInputController::~XInputController()
{
	//
}

/// <summary>
/// Is controller connected
/// </summary>
/// <param name="controllerID">Controller ID</param>
/// <returns>"true" if connected, otherwise "false"</returns>
bool XInputController::IsConnected(int controllerID)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// TODO
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	XINPUT_STATE state;
	return (XInputGetState(static_cast<DWORD>(controllerID), &state) == 0);
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
}

/// <summary>
/// Get controller buttons
/// </summary>
/// <param name="controllerID">Controller ID</param>
/// <returns>Controller buttons</returns>
EXInputButtons XInputController::GetButtons(int controllerID)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// TODO
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	XINPUT_STATE state;
	XInputGetState(static_cast<DWORD>(controllerID), &state);
	return static_cast<EXInputButtons>(state.Gamepad.wButtons);
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
}

/// <summary>
/// Get controller axis
/// </summary>
/// <param name="controllerID">Controller ID</param>
/// <param name="axis">Axis</param>
/// <returns>Axis value between -1.0 and 1.0</returns>
float XInputController::GetAxis(int controllerID, EXInputAxis axis)
{
	float ret(0.0f);
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// TODO
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	XINPUT_STATE state;
	if (XInputGetState(static_cast<DWORD>(controllerID), &state) == 0L)
	{
		switch (axis)
		{
		case EXInputAxis_ThumbLX:
			ret = state.Gamepad.sThumbLX / 32767.0f;
			break;
		case EXInputAxis_ThumbLY:
			ret = state.Gamepad.sThumbLY / 32767.0f;
			break;
		case EXInputAxis_ThumbRX:
			ret = state.Gamepad.sThumbRX / 32767.0f;
			break;
		case EXInputAxis_ThumbRY:
			ret = state.Gamepad.sThumbRY / 32767.0f;
			break;
		case EXInputAxis_LeftTrigger:
			ret = state.Gamepad.bLeftTrigger / 255.0f;
			break;
		case EXInputAxis_RightTrigger:
			ret = state.Gamepad.bRightTrigger / 255.0f;
			break;
		}
	}
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
	return ret;
}

/// <summary>
/// Set controller vibration
/// </summary>
/// <param name="controllerID">Controller ID</param>
/// <param name="leftMotor">Left motor</param>
/// <param name="rightMotor">Right motor</param>
void XInputController::SetVibration(int controllerID, float leftMotor, float rightMotor)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// TODO
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	XINPUT_VIBRATION vibration;
	if (leftMotor > 1.0f)
	{
		leftMotor = 1.0f;
	}
	else if (leftMotor < -1.0f)
	{
		leftMotor = -1.0f;
	}
	if (rightMotor > 1.0f)
	{
		rightMotor = 1.0f;
	}
	else if (rightMotor < -1.0f)
	{
		rightMotor = -1.0f;
	}
	vibration.wLeftMotorSpeed = static_cast<WORD>(leftMotor * 65535.0);
	vibration.wRightMotorSpeed = static_cast<WORD>(rightMotor * 65535.0);
	XInputSetState(controllerID, &vibration);
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
}

/// <summary>
/// Get controller audio device IDs
/// </summary>
/// <param name="controllerID">Controller ID</param>
/// <param name="renderDeviceID">Render device ID</param>
/// <param name="captureDeviceID">Capture device ID</param>
void XInputController::GetAudioDeviceIDs(int controllerID, wstring & renderDeviceID, wstring & captureDeviceID)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// TODO
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	wstring render_device_id(256UL, L'\0');
	unsigned int render_device_id_len(256U);
	wstring capture_device_id(256UL, L'\0');
	unsigned int capture_device_id_len(256U);
	renderDeviceID.clear();
	captureDeviceID.clear();
	if (XInputGetAudioDeviceIds(static_cast<WORD>(controllerID), &(render_device_id[0]), &render_device_id_len, &(capture_device_id[0]), &capture_device_id_len) == ERROR_SUCCESS)
	{
		render_device_id.resize(render_device_id_len, L'\0');
		capture_device_id.resize(capture_device_id_len, L'\0');
		renderDeviceID = render_device_id;
		captureDeviceID = capture_device_id;
	}
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
}

/// <summary>
/// Get controller battery information
/// </summary>
/// <param name="controllerID">Controller ID</param>
/// <param name="batteryDeviceType">Battery device type</param>
/// <param name="batteryInformation">Battery information</param>
/// <returns>Battery information</returns>
XInputBatteryInformation & XInputController::GetBatteryInformation(int controllerID, EXInputBatteryDeviceType batteryDeviceType, XInputBatteryInformation & batteryInformation)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// TODO
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	XINPUT_BATTERY_INFORMATION battery_information = { 0 };
	if (XInputGetBatteryInformation(static_cast<WORD>(controllerID), batteryDeviceType, &battery_information) == ERROR_SUCCESS)
	{
		batteryInformation.batteryType = static_cast<EXInputBatteryType>(battery_information.BatteryType);
		batteryInformation.batteryLevel = static_cast<EXInputBatteryLevel>(battery_information.BatteryLevel);
	}
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
	return batteryInformation;
}

/// <summary>
/// Get controller XInput capabilities
/// </summary>
/// <param name="controllerID">Controller ID</param>
/// <param name="capabilties">Controller XInput capabilities</param>
/// <returns>Controller XInput capabilities</returns>
XInputCapabilities & XInputController::GetCapabilities(int controllerID, XInputCapabilities & capabilities)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// TODO
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	XINPUT_CAPABILITIES xinput_capabilities = { 0 };
	if (XInputGetCapabilities(static_cast<WORD>(controllerID), XINPUT_FLAG_GAMEPAD, &xinput_capabilities) == ERROR_SUCCESS)
	{
		capabilities.deviceType = static_cast<EXInputDeviceType>(xinput_capabilities.Type);
		capabilities.deviceSubType = static_cast<EXInputDeviceSubType>(xinput_capabilities.SubType);
		capabilities.deviceFeatures = static_cast<EXInputDeviceFeatures>(xinput_capabilities.Flags);
		capabilities.buttons = static_cast<EXInputButtons>(xinput_capabilities.Gamepad.wButtons);
		capabilities.leftTrigger = xinput_capabilities.Gamepad.bLeftTrigger / 255.0f;
		capabilities.rightTrigger = xinput_capabilities.Gamepad.bRightTrigger / 255.0f;
		capabilities.thumbLX = xinput_capabilities.Gamepad.sThumbLX / 32767.0f;
		capabilities.thumbLY = xinput_capabilities.Gamepad.sThumbLY / 32767.0f;
		capabilities.thumbRX = xinput_capabilities.Gamepad.sThumbRX / 32767.0f;
		capabilities.thumbRY = xinput_capabilities.Gamepad.sThumbRY / 32767.0f;
		capabilities.leftMotor = xinput_capabilities.Vibration.wLeftMotorSpeed / 65.535f;
		capabilities.rightMotor = xinput_capabilities.Vibration.wRightMotorSpeed / 65.535f;
	}
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
	return capabilities;
}

/// <summary>
/// Get controller keystroke
/// </summary>
/// <param name="controllerID">Controller ID</param>
/// <param name="keystroke">Controller keystroke</param>
/// <returns>Controller keystroke</returns>
XInputKeystroke & XInputController::GetKeystroke(int controllerID, XInputKeystroke & keystroke)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// TODO
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	XINPUT_KEYSTROKE xinput_keystroke = { 0 };
	if (XInputGetKeystroke(static_cast<WORD>(controllerID), 0, &xinput_keystroke) == ERROR_SUCCESS)
	{
		keystroke.virtualKey = static_cast<EXInputVirtualKey>(xinput_keystroke.VirtualKey);
		keystroke.unicode = xinput_keystroke.Unicode;
		keystroke.keyboardStates = static_cast<EXInputKeyboardStates>(xinput_keystroke.Flags);
		keystroke.userIndex = xinput_keystroke.UserIndex;
		keystroke.hidCode = xinput_keystroke.HidCode;
	}
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
	return keystroke;
}
