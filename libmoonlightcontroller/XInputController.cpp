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

XInputController::XInputController()
#if defined(MOONLIGHT_CONTROLLER_LINUX)
	: userInputOutput(EUserInputOutputType_Gamepad, "Moonlight controller (Gamepad)")
#endif
{
	//
}

XInputController::~XInputController()
{
	//
}

bool XInputController::IsConnected(int controllerID)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	XINPUT_STATE state;
	return (XInputGetState(static_cast<DWORD>(controllerID), &state) == 0L);
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// To-do
#endif
}

EXInputButtons XInputController::GetButtons(int controllerID)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	XINPUT_STATE state;
	XInputGetState(static_cast<DWORD>(controllerID), &state);
	return static_cast<EXInputButtons>(state.Gamepad.wButtons);
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// To-do
#endif
}

float XInputController::GetAxis(int controllerID, EXInputAxis axis)
{
	float ret(0.0f);
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
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
// To-do
#endif
	return ret;
}

void XInputController::SetVibration(int controllerID, float leftMotor, float rightMotor)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
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
// To-do
#endif
}

void XInputController::GetAudioDeviceIDs(int controllerID, wstring & renderDeviceID, wstring & captureDeviceID)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	wchar_t render_device_id[256] = { L'\0' };
	unsigned int render_device_id_len = 256;
	wchar_t capture_device_id[256] = { L'\0' };
	unsigned int capture_device_id_len = 256;
	renderDeviceID.clear();
	captureDeviceID.clear();
	if (XInputGetAudioDeviceIds(static_cast<WORD>(controllerID), render_device_id, &render_device_id_len, capture_device_id, &capture_device_id_len) == ERROR_SUCCESS)
	{
		renderDeviceID = render_device_id;
		captureDeviceID = capture_device_id;
	}
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
// To-do
#endif
}

XInputBatteryInformation XInputController::GetBatteryInformation(int controllerID, EXInputBatteryDeviceType batteryDeviceType)
{
	XInputBatteryInformation ret;
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	XINPUT_BATTERY_INFORMATION battery_information;
	if (XInputGetBatteryInformation(static_cast<WORD>(controllerID), batteryDeviceType, &battery_information) == ERROR_SUCCESS)
	{
		ret.batteryType = static_cast<EXInputBatteryType>(battery_information.BatteryType);
		ret.batteryLevel = static_cast<EXInputBatteryLevel>(battery_information.BatteryLevel);
	}
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// To-do
#endif
	return ret;
}

XInputCapabilities XInputController::GetCapabilities(int controllerID)
{
	XInputCapabilities ret;
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	XINPUT_CAPABILITIES capabilities;
	if (XInputGetCapabilities(static_cast<WORD>(controllerID), XINPUT_FLAG_GAMEPAD, &capabilities) == ERROR_SUCCESS)
	{
		ret.deviceType = static_cast<EXInputDeviceType>(capabilities.Type);
		ret.deviceSubType = static_cast<EXInputDeviceSubType>(capabilities.SubType);
		ret.deviceFeatures = static_cast<EXInputDeviceFeatures>(capabilities.Flags);
		ret.buttons = static_cast<EXInputButtons>(capabilities.Gamepad.wButtons);
		ret.leftTrigger = capabilities.Gamepad.bLeftTrigger / 255.0f;
		ret.rightTrigger = capabilities.Gamepad.bRightTrigger / 255.0f;
		ret.thumbLX = capabilities.Gamepad.sThumbLX / 32767.0f;
		ret.thumbLY = capabilities.Gamepad.sThumbLY / 32767.0f;
		ret.thumbRX = capabilities.Gamepad.sThumbRX / 32767.0f;
		ret.thumbRY = capabilities.Gamepad.sThumbRY / 32767.0f;
		ret.leftMotor = capabilities.Vibration.wLeftMotorSpeed / 65.535f;
		ret.rightMotor = capabilities.Vibration.wRightMotorSpeed / 65.535f;
	}
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// To-do
#endif
	return ret;
}

XInputKeystroke XInputController::GetKeystroke(int controllerID)
{
	XInputKeystroke ret;
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	XINPUT_KEYSTROKE keystroke;
	if (XInputGetKeystroke(static_cast<WORD>(controllerID), 0, &keystroke) == ERROR_SUCCESS)
	{
		ret.virtualKey = static_cast<EXInputVirtualKey>(keystroke.VirtualKey);
		ret.unicode = keystroke.Unicode;
		ret.keyboardStates = static_cast<EXInputKeyboardStates>(keystroke.Flags);
		ret.userIndex = keystroke.UserIndex;
		ret.hidCode = keystroke.HidCode;
	}
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// To-do
#endif
	return ret;
}
