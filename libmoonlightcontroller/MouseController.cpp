#define MOONLIGHT_CONTROLLER_LIBRARY
#include <libmoonlightcontroller/MouseController.h>
#include <libmoonlightcontroller/Platform.h>

#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	include <linux/uinput.h>
#endif

using namespace MoonlightController;

/// <summary>
/// Is mouse button down
/// </summary>
static bool isDown[3] = { false };

/// <summary>
/// Default constructor
/// </summary>
MouseController::MouseController()
#if defined(MOONLIGHT_CONTROLLER_LINUX)
	: userInputOutput(EUserInputOutputType_Mouse, "Moonlight controller (Mouse)")
#endif
{
	//
}

/// <summary>
/// Destructor
/// </summary>
MouseController::~MouseController()
{
	//
}

/// <summary>
/// Set mouse position
/// </summary>
/// <param name="x">Mouse X</param>
/// <param name="y">Mouse Y</param>
void MouseController::SetPosition(int x, int y)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
	userInputOutput.write(EV_ABS, ABS_X, x);
	userInputOutput.write(EV_ABS, ABS_Y, y);
	userInputOutput.write(EV_SYN, SYN_REPORT, 0);
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	POINT p;
	p.x = x;
	p.y = y;
	SetCursorPos(p.x, p.y);
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
}

/// <summary>
/// Get mouse position
/// </summary>
/// <param name="position">Mouse position</param>
/// <returns>Mouse position</returns>
Position & MouseController::GetPosition(Position & position)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// TODO
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	POINT p = { 0 };
	if (GetCursor() != NULL)
	{
		GetCursorPos(&p);
	}
	position.x = p.x;
	position.y = p.y;
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
	return position;
}

/// <summary>
/// Move mouse (relative)
/// </summary>
/// <param name="x">Mouse X</param>
/// <param name="y">Mouse Y</param>
void MouseController::Move(int x, int y)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
	userInputOutput.write(EV_REL, REL_X, x);
	userInputOutput.write(EV_REL, REL_Y, y);
	userInputOutput.write(EV_SYN, SYN_REPORT, 0);
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	POINT p;
	if (GetCursor() != NULL)
	{
		GetCursorPos(&p);
		p.x += x;
		p.y += y;
		SetCursorPos(p.x, p.y);
	}
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
}

/// <summary>
/// Mouse click
/// </summary>
/// <param name="mouseButton">Mouse button</param>
void MouseController::Click(EMouseButton button)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
	switch (button)
	{
	case EMouseButton_Left:
		userInputOutput.write(EV_KEY, BTN_LEFT, 1);
		break;
	case EMouseButton_Right:
		userInputOutput.write(EV_KEY, BTN_RIGHT, 1);
		break;
	case EMouseButton_Middle:
		userInputOutput.write(EV_KEY, BTN_MIDDLE, 1);
		break;
	}
	userInputOutput.write(EV_SYN, SYN_REPORT, 0);
	switch (button)
	{
	case EMouseButton_Left:
		userInputOutput.write(EV_KEY, BTN_LEFT, 0);
		break;
	case EMouseButton_Right:
		userInputOutput.write(EV_KEY, BTN_RIGHT, 0);
		break;
	case EMouseButton_Middle:
		userInputOutput.write(EV_KEY, BTN_MIDDLE, 0);
		break;
	}
	userInputOutput.write(EV_SYN, SYN_REPORT, 0);
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	INPUT in = { 0 };
	in.type = INPUT_MOUSE;
	switch (button)
	{
	case EMouseButton_Left:
		in.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		break;
	case EMouseButton_Right:
		in.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		break;
	case EMouseButton_Middle:
		in.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
		break;
	}
	SendInput(1, &in, sizeof(INPUT));
	switch (button)
	{
	case EMouseButton_Left:
		in.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		break;
	case EMouseButton_Right:
		in.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		break;
	case EMouseButton_Middle:
		in.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
		break;
	}
	in.mi.dwExtraInfo = GetMessageExtraInfo();
	SendInput(1, &in, sizeof(INPUT));
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
}

/// <summary>
/// Mouse press
/// </summary>
/// <param name="button">Mouse button</param>
/// <param name="down">Press down</param>
void MouseController::Press(EMouseButton button, bool down)
{
	if (down ? (!IsDown(button)) : IsDown(button))
	{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
		switch (button)
		{
		case EMouseButton_Left:
			userInputOutput.write(EV_KEY, BTN_LEFT, down ? 1 : 0);
			isDown[mouseButton] = down;
			break;
		case EMouseButton_Right:
			userInputOutput.write(EV_KEY, BTN_RIGHT, down ? 1 : 0);
			isDown[mouseButton] = down;
			break;
		case EMouseButton_Middle:
			userInputOutput.write(EV_KEY, BTN_MIDDLE, down ? 1 : 0);
			isDown[mouseButton] = down;
			break;
		}
		userInputOutput.write(EV_SYN, SYN_REPORT, 0);
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
		INPUT in = { 0 };
		in.type = INPUT_MOUSE;
		switch (button)
		{
		case EMouseButton_Left:
			in.mi.dwFlags = (down ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP);
			isDown[button] = down;
			break;
		case EMouseButton_Right:
			in.mi.dwFlags = (down ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP);
			isDown[button] = down;
			break;
		case EMouseButton_Middle:
			in.mi.dwFlags = (down ? MOUSEEVENTF_MIDDLEDOWN : MOUSEEVENTF_MIDDLEUP);
			isDown[button] = down;
			break;
		}
		in.mi.dwExtraInfo = GetMessageExtraInfo();
		SendInput(1, &in, sizeof(INPUT));
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
		// TODO
#endif
	}
}

/// <summary>
/// Is mouse down
/// </summary>
/// <param name="button">Mouse button</param>
/// <returns>"true" if mouse button is down, otherwise "false"</returns>
bool MouseController::IsDown(EMouseButton button)
{
	bool ret(false);
	switch (button)
	{
	case EMouseButton_Left:
	case EMouseButton_Right:
	case EMouseButton_Middle:
		ret = isDown[button];
		break;
	}
	return ret;
}

/// <summary>
/// Scroll mouse wheel
/// </summary>
/// <param name="scroll">Scroll</param>
void MouseController::Scroll(int scroll)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// TODO
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	INPUT in = { 0 };
	in.type = INPUT_MOUSE;
	in.mi.mouseData = scroll;
	in.mi.dwFlags = MOUSEEVENTF_WHEEL;
	in.mi.dwExtraInfo = GetMessageExtraInfo();
	SendInput(1, &in, sizeof(INPUT));
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// TODO
#endif
}
