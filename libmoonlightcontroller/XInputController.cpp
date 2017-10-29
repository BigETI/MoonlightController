#define MOONLIGHT_CONTROLLER_LIBRARY
#include <XInputController.h>
#include <platform.h>
#include <Xinput.h>

using namespace MoonlightController;

bool XInputController::IsConnected(int controllerID)
{
	XINPUT_STATE state;
	return (XInputGetState(static_cast<DWORD>(controllerID), &state) == 0L);
}

EXInputButton XInputController::GetButtons(int controllerID)
{
	XINPUT_STATE state;
	XInputGetState(static_cast<DWORD>(controllerID), &state);
	return static_cast<EXInputButton>(state.Gamepad.wButtons);
}

float XInputController::GetAxis(int controllerID, EXInputAxis axis)
{
	float ret(0.0f);
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
	return ret;
}

void XInputController::SetVibration(int controllerID, float leftMotor, float rightMotor)
{
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
}
