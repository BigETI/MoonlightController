#include <Windows.h>

#include <string_view>

#include <Controllers/Keyboard/IKeyboardController.hpp>
#include <Platforms/Windows/Controllers/Keyboard/KeyboardController.hpp>

using namespace MoonlightController::Controllers::Keyboard;
using namespace MoonlightController::Platforms::Windows::Controllers::Keyboard;
using namespace std;

KeyboardController::KeyboardController() {
	//
}

KeyboardController::KeyboardController(const KeyboardController& keyboardController) {
	// ...
}

KeyboardController::KeyboardController(KeyboardController&& keyboardController) noexcept {
	// ...
}

bool KeyboardController::ClickKey(int keyCode) const noexcept {
	INPUT in = { 0 };
	in.type = INPUT_KEYBOARD;
	in.ki.wVk = static_cast<WORD>(keyCode);
	in.ki.dwExtraInfo = GetMessageExtraInfo();
	bool ret(SendInput(1, &in, sizeof(INPUT)) > 0U);
	if (ret) {
		in.ki.dwFlags = KEYEVENTF_KEYUP;
		in.ki.dwExtraInfo = GetMessageExtraInfo();
		ret = SendInput(1, &in, sizeof(INPUT)) > 0U;
	}
	return ret;
}

bool KeyboardController::PressKey(int keyCode) const noexcept {
	bool ret(!IsKeyDown(keyCode));
	if (ret) {
		INPUT in = { 0 };
		in.type = INPUT_KEYBOARD;
		in.ki.wVk = static_cast<WORD>(keyCode);
		ret = SendInput(1, &in, sizeof(INPUT)) > 0U;
	}
	return ret;
}

bool KeyboardController::ReleaseKey(int keyCode) const noexcept {
	bool ret(IsKeyDown(keyCode));
	if (ret) {
		INPUT in = { 0 };
		in.type = INPUT_KEYBOARD;
		in.ki.wVk = static_cast<WORD>(keyCode);
		in.ki.dwFlags = KEYEVENTF_KEYUP;
		ret = SendInput(1, &in, sizeof(INPUT)) > 0U;
	}
	return ret;
}

bool KeyboardController::IsKeyDown(int keyCode) const noexcept {
	return (GetKeyState(keyCode) & 0x800) == 0x800;
}

bool KeyboardController::AppendTextAsKeystrokes(string_view textAsInput) const noexcept {
	bool ret(true);
	INPUT in = { 0 };
	in.type = INPUT_KEYBOARD;
	for (const auto& character : textAsInput) {
		in.ki.wScan = character;
		in.ki.dwFlags = KEYEVENTF_UNICODE;
		in.ki.dwExtraInfo = GetMessageExtraInfo();
		ret = SendInput(1, &in, sizeof(INPUT)) > 0U;
		if (!ret) {
			break;
		}
		in.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
		in.ki.dwExtraInfo = GetMessageExtraInfo();
		ret = SendInput(1, &in, sizeof(INPUT)) > 0U;
		if (!ret) {
			break;
		}
	}
	return ret;
}

KeyboardController& KeyboardController::operator =(const KeyboardController& keyboardController) {
	return *this;
}

KeyboardController& KeyboardController::operator =(KeyboardController&& keyboardController) noexcept {
	return *this;
}
