#include <Windows.h>

#include <Controllers/Mouse/EMouseButton.hpp>
#include <Platforms/Windows/Controllers/Mouse/MouseController.hpp>
#include <Position2D.hpp>
#include <Vector2D.hpp>

using namespace MoonlightController;
using namespace MoonlightController::Controllers::Mouse;
using namespace MoonlightController::Platforms::Windows::Controllers::Mouse;

MouseController::MouseController() {
	//
}

MouseController::MouseController(const MouseController& mouseController) {
	// ...
}

MouseController::MouseController(MouseController&& mouseController) noexcept {
	// ...
}

bool MouseController::IsConnected() const noexcept {
	return GetCursor() != NULL;
}

bool MouseController::SetCursorPosition(int x, int y) const noexcept {
	return static_cast<bool>(SetCursorPos(x, y));
}

bool MouseController::SetCursorPosition(const Position2D<int>& position) const noexcept {
	return SetCursorPosition(position.x, position.y);
}

bool MouseController::TryGettingPosition(Position2D<int>& result) const noexcept {
	POINT position = { 0 };
	bool ret(IsConnected() && GetCursorPos(&position));
	if (ret) {
		result.x = position.x;
		result.y = position.y;
	}
	return ret;
}

bool MouseController::MoveCursor(int x, int y) const noexcept {
	POINT position;
	bool ret(IsConnected() && GetCursorPos(&position));
	if (ret) {
		position.x += x;
		position.y += y;
		ret = static_cast<bool>(SetCursorPos(position.x, position.y));
	}
	return ret;
}

bool MouseController::MoveCursor(const Vector2D<int>& movement) const noexcept {
	return MoveCursor(movement.x, movement.y);
}

bool MouseController::ClickButton(EMouseButton button) const noexcept {
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	switch (button) {
	case EMouseButton::Left:
		input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		break;
	case EMouseButton::Right:
		input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		break;
	case EMouseButton::Middle:
		input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
		break;
	}
	bool ret(SendInput(1, &input, sizeof(INPUT)) > 0U);
	if (ret) {
		switch (button) {
		case EMouseButton::Left:
			input.mi.dwFlags = static_cast<DWORD>(MOUSEEVENTF_LEFTUP);
			break;
		case EMouseButton::Right:
			input.mi.dwFlags = static_cast<DWORD>(MOUSEEVENTF_RIGHTUP);
			break;
		case EMouseButton::Middle:
			input.mi.dwFlags = static_cast<DWORD>(MOUSEEVENTF_MIDDLEUP);
			break;
		}
		input.mi.dwExtraInfo = GetMessageExtraInfo();
		ret = SendInput(1, &input, sizeof(INPUT)) > 0U;
	}
	return ret;
}

bool MouseController::PressButton(EMouseButton button) const noexcept {
	bool ret(!IsButtonDown(button));
	if (ret) {
		INPUT input = { 0 };
		input.type = INPUT_MOUSE;
		switch (button) {
		case EMouseButton::Left:
			input.mi.dwFlags = static_cast<DWORD>(MOUSEEVENTF_LEFTDOWN);
			break;
		case EMouseButton::Right:
			input.mi.dwFlags = static_cast<DWORD>(MOUSEEVENTF_RIGHTDOWN);
			break;
		case EMouseButton::Middle:
			input.mi.dwFlags = static_cast<DWORD>(MOUSEEVENTF_MIDDLEDOWN);
			break;
		}
		input.mi.dwExtraInfo = GetMessageExtraInfo();
		ret = SendInput(1, &input, sizeof(INPUT)) > 0U;
	}
	return ret;
}

bool MouseController::ReleaseButton(EMouseButton button) const noexcept {
	bool ret(IsButtonDown(button));
	if (ret) {
		INPUT input = { 0 };
		input.type = INPUT_MOUSE;
		switch (button) {
		case EMouseButton::Left:
			input.mi.dwFlags = static_cast<DWORD>(MOUSEEVENTF_LEFTUP);
			break;
		case EMouseButton::Right:
			input.mi.dwFlags = static_cast<DWORD>(MOUSEEVENTF_RIGHTUP);
			break;
		case EMouseButton::Middle:
			input.mi.dwFlags = static_cast<DWORD>(MOUSEEVENTF_MIDDLEUP);
			break;
		}
		input.mi.dwExtraInfo = GetMessageExtraInfo();
		ret = SendInput(1, &input, sizeof(INPUT)) > 0U;
	}
	return ret;
}

bool MouseController::IsButtonDown(EMouseButton button) const noexcept {
	int key_code(0);
	switch (button) {
	case EMouseButton::Left:
		key_code = VK_LBUTTON;
		break;
	case EMouseButton::Right:
		key_code = VK_RBUTTON;
		break;
	case EMouseButton::Middle:
		key_code = VK_MBUTTON;
		break;
	}
	return ((GetKeyState(key_code) & 0x800) == 0x800);
}

bool MouseController::ScrollWheel(int scroll) const noexcept {
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.mouseData = scroll;
	input.mi.dwFlags = MOUSEEVENTF_WHEEL;
	input.mi.dwExtraInfo = GetMessageExtraInfo();
	return SendInput(1, &input, sizeof(INPUT)) > 0U;
}

MouseController& MouseController::operator =(const MouseController& mouseController) {
	return *this;
}

MouseController& MouseController::operator =(MouseController&& mouseController) noexcept {
	return *this;
}
