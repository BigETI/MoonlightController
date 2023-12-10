#include <algorithm>
#include <cstddef>
#include <cstring>
#include <string>
#include <utility>

#include <Windows.h>
#include <Xinput.h>

#include <Controllers/XInput/EXInputButtons.hpp>
#include <Controllers/XInput/EXInputAxis.hpp>
#include <Controllers/XInput/XInputBatteryInformation.hpp>
#include <Controllers/XInput/EXInputBatteryDeviceType.hpp>
#include <Controllers/XInput/XInputCapabilities.hpp>
#include <Controllers/XInput/XInputKeystroke.hpp>
#include <Platforms/Windows/Controllers/XInput/XInputController.hpp>

using namespace MoonlightController::Controllers::XInput;
using namespace MoonlightController::Platforms::Windows::Controllers::XInput;
using namespace std;

XInputController::XInputController(size_t index) : index(index) {
	// ...
}

XInputController::XInputController(const XInputController& xInputController) : index(xInputController.index) {
	// ...
}

XInputController::XInputController(XInputController&& xInputController) noexcept : index(std::move(xInputController.index)) {
	// ...
}

size_t XInputController::GetIndex() const noexcept {
	return index;
}

bool XInputController::IsConnected() const noexcept {
	XINPUT_STATE state;
	return (XInputGetState(static_cast<DWORD>(index), &state) == ERROR_SUCCESS);
}

bool XInputController::TryGettingPressedButtons(EXInputButtons& result) const noexcept {
	XINPUT_STATE state;
	bool ret(XInputGetState(static_cast<DWORD>(index), &state) == ERROR_SUCCESS);
	if (ret) {
		result = static_cast<EXInputButtons>(state.Gamepad.wButtons);
	}
	return ret;
}

bool XInputController::TryGettingAxisValue(EXInputAxis axis, float& result) const noexcept {
	XINPUT_STATE state;
	bool ret(XInputGetState(static_cast<DWORD>(index), &state) == ERROR_SUCCESS);
	if (ret) {
		switch (axis) {
		case EXInputAxis::ThumbLX:
			result = state.Gamepad.sThumbLX / 32767.0f;
			break;
		case EXInputAxis::ThumbLY:
			result = state.Gamepad.sThumbLY / 32767.0f;
			break;
		case EXInputAxis::ThumbRX:
			result = state.Gamepad.sThumbRX / 32767.0f;
			break;
		case EXInputAxis::ThumbRY:
			result = state.Gamepad.sThumbRY / 32767.0f;
			break;
		case EXInputAxis::LeftTrigger:
			result = state.Gamepad.bLeftTrigger / 255.0f;
			break;
		case EXInputAxis::RightTrigger:
			result = state.Gamepad.bRightTrigger / 255.0f;
			break;
		}
	}
	return ret;
}

bool XInputController::SetVibration(float leftMotor, float rightMotor) const noexcept {
	XINPUT_VIBRATION vibration;
	vibration.wLeftMotorSpeed = static_cast<WORD>(clamp(leftMotor, -1.0f, 1.0f) * 65535.0);
	vibration.wRightMotorSpeed = static_cast<WORD>(clamp(rightMotor, -1.0f, 1.0f) * 65535.0);
	return XInputSetState(index, &vibration) == ERROR_SUCCESS;
}

bool XInputController::TryGettingAudioDeviceIDs(wstring& renderDeviceID, wstring& captureDeviceID) const noexcept {
	constexpr static const size_t maximal_string_buffer_size(256);
	UINT render_device_id_len(static_cast<UINT>(maximal_string_buffer_size));
	UINT capture_device_id_len(static_cast<UINT>(maximal_string_buffer_size));
	renderDeviceID.resize(maximal_string_buffer_size + static_cast<size_t>(1));
	memset(renderDeviceID.data(), 0, renderDeviceID.size() * sizeof(wstring::value_type));
	captureDeviceID.resize(maximal_string_buffer_size + static_cast<size_t>(1));
	memset(captureDeviceID.data(), 0, renderDeviceID.size() * sizeof(wstring::value_type));
	bool ret(
		XInputGetAudioDeviceIds(
			static_cast<WORD>(index),
			reinterpret_cast<LPWSTR>(renderDeviceID.data()),
			&render_device_id_len,
			reinterpret_cast<LPWSTR>(captureDeviceID.data()),
			&capture_device_id_len
		) == ERROR_SUCCESS
	);
	if (ret) {
		renderDeviceID.resize(render_device_id_len);
		captureDeviceID.resize(capture_device_id_len);
	}
	else {
		renderDeviceID.clear();
		captureDeviceID.clear();
	}
	return ret;
}

bool XInputController::TryGettingBatteryInformation(EXInputBatteryDeviceType batteryDeviceType, XInputBatteryInformation& result) const noexcept {
	XINPUT_BATTERY_INFORMATION battery_information = { 0 };
	bool ret(XInputGetBatteryInformation(static_cast<WORD>(index), static_cast<BYTE>(batteryDeviceType), &battery_information) == ERROR_SUCCESS);
	if (ret) {
		result.batteryType = static_cast<EXInputBatteryType>(battery_information.BatteryType);
		result.batteryLevel = static_cast<EXInputBatteryLevel>(battery_information.BatteryLevel);
	}
	return ret;
}

bool XInputController::TryGettingCapabilities(XInputCapabilities& result) const noexcept {
	XINPUT_CAPABILITIES xinput_capabilities = { 0 };
	bool ret(XInputGetCapabilities(static_cast<WORD>(index), XINPUT_FLAG_GAMEPAD, &xinput_capabilities) == ERROR_SUCCESS);
	if (ret) {
		result.deviceType = static_cast<EXInputDeviceType>(xinput_capabilities.Type);
		result.deviceSubType = static_cast<EXInputDeviceSubType>(xinput_capabilities.SubType);
		result.deviceFeatures = static_cast<EXInputDeviceFeatures>(xinput_capabilities.Flags);
		result.buttons = static_cast<EXInputButtons>(xinput_capabilities.Gamepad.wButtons);
		result.leftTrigger = xinput_capabilities.Gamepad.bLeftTrigger / 255.0f;
		result.rightTrigger = xinput_capabilities.Gamepad.bRightTrigger / 255.0f;
		result.thumbLX = xinput_capabilities.Gamepad.sThumbLX / 32767.0f;
		result.thumbLY = xinput_capabilities.Gamepad.sThumbLY / 32767.0f;
		result.thumbRX = xinput_capabilities.Gamepad.sThumbRX / 32767.0f;
		result.thumbRY = xinput_capabilities.Gamepad.sThumbRY / 32767.0f;
		result.leftMotor = xinput_capabilities.Vibration.wLeftMotorSpeed / 65.535f;
		result.rightMotor = xinput_capabilities.Vibration.wRightMotorSpeed / 65.535f;
	}
	return ret;
}

bool XInputController::TryGettingKeystroke(XInputKeystroke& result) const noexcept {
	XINPUT_KEYSTROKE xinput_keystroke = { 0 };
	bool ret(XInputGetKeystroke(static_cast<WORD>(index), 0, &xinput_keystroke) == ERROR_SUCCESS);
	if (ret) {
		result.virtualKey = static_cast<EXInputVirtualKey>(xinput_keystroke.VirtualKey);
		result.unicode = xinput_keystroke.Unicode;
		result.keyboardStates = static_cast<EXInputKeyboardStates>(xinput_keystroke.Flags);
		result.userIndex = xinput_keystroke.UserIndex;
		result.hidCode = xinput_keystroke.HidCode;
	}
	return ret;
}

XInputController& XInputController::operator =(const XInputController& xInputController) {
	index = xInputController.index;
	return *this;
}

XInputController& XInputController::operator =(XInputController&& xInputController) noexcept {
	index = std::move(xInputController.index);
	return *this;
}
