#define MOONLIGHT_CONTROLLER_LIBRARY
#include <libmoonlightcontroller/MouseController.h>
#include <libmoonlightcontroller/Platform.h>

using namespace MoonlightController;

#if defined(MOONLIGHT_CONTROLLER_WINDOWS)
static bool isDown[3] = { false };
#endif

void MouseController::SetPosition(int x, int y)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	POINT p;
	p.x = x;
	p.y = y;
	SetCursorPos(p.x, p.y);
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// To-do
#endif
}

Position MouseController::GetPosition()
{
	Position ret;
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	POINT p;
	if (GetCursor() != NULL)
	{
		GetCursorPos(&p);
		ret.x = p.x;
		ret.y = p.y;
	}
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// To-do
#endif
	return ret;
}

void MouseController::Move(int x, int y)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
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
	// To-do
#endif
}

void MouseController::Click(EMouseButton mouseButton)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	INPUT in;
	memset(&in, 0, sizeof(INPUT));
	in.type = INPUT_MOUSE;
	switch (mouseButton)
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
	switch (mouseButton)
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
	// To-do
#endif
}

void MouseController::Press(EMouseButton mouseButton, bool down)
{
	if (down ? (!IsDown(mouseButton)) : IsDown(mouseButton))
	{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
		// To-do
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
		INPUT in;
		memset(&in, 0, sizeof(INPUT));
		in.type = INPUT_MOUSE;
		switch (mouseButton)
		{
		case EMouseButton_Left:
			in.mi.dwFlags = (down ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP);
			isDown[mouseButton] = down;
			break;
		case EMouseButton_Right:
			in.mi.dwFlags = (down ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP);
			isDown[mouseButton] = down;
			break;
		case EMouseButton_Middle:
			in.mi.dwFlags = (down ? MOUSEEVENTF_MIDDLEDOWN : MOUSEEVENTF_MIDDLEUP);
			isDown[mouseButton] = down;
			break;
		}
		in.mi.dwExtraInfo = GetMessageExtraInfo();
		SendInput(1, &in, sizeof(INPUT));
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
		// To-do
#endif
	}
}

bool MouseController::IsDown(EMouseButton mouseButton)
{
	bool ret(false);
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	//#	error Implement function here
	switch (mouseButton)
	{
	case EMouseButton_Left:
	case EMouseButton_Right:
	case EMouseButton_Middle:
		ret = isDown[mouseButton];
		break;
	}
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// To-do
#endif
	return ret;
}

void MouseController::Scroll(int scroll)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
#	error Implement function here
	// To-do
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	INPUT in;
	memset(&in, 0, sizeof(INPUT));
	in.type = INPUT_MOUSE;
	in.mi.mouseData = scroll;
	in.mi.dwFlags = MOUSEEVENTF_WHEEL;
	in.mi.dwExtraInfo = GetMessageExtraInfo();
	SendInput(1, &in, sizeof(INPUT));
#elif defined(MOONLIGHT_CONTROLLER_OSX)
#	error Implement function here
	// To-do
#endif
}
