#pragma once

#include <cstddef>
#include <string>

#include "EXInputAxis.hpp"
#include "EXInputBatteryDeviceType.hpp"
#include "EXInputButtons.hpp"
#include "XInputBatteryInformation.hpp"
#include "XInputCapabilities.hpp"
#include "XInputKeystroke.hpp"

namespace MoonlightController::Controllers::XInput {
	class IXInputController {
	public:

		constexpr virtual ~IXInputController() {
			// ...
		}

		virtual std::size_t GetIndex() const noexcept = 0;

		virtual bool IsConnected() const noexcept = 0;

		virtual bool TryGettingPressedButtons(EXInputButtons& result) const noexcept = 0;

		virtual bool TryGettingAxisValue(EXInputAxis axis, float& result) const noexcept = 0;

		virtual bool SetVibration(float leftMotor, float rightMotor) const noexcept = 0;

		virtual bool TryGettingAudioDeviceIDs(std::wstring& outRenderDeviceID, std::wstring& outCaptureDeviceID) const noexcept = 0;

		virtual bool TryGettingBatteryInformation(EXInputBatteryDeviceType batteryDeviceType, XInputBatteryInformation& result) const noexcept = 0;

		virtual bool TryGettingCapabilities(XInputCapabilities& result) const noexcept = 0;

		virtual bool TryGettingKeystroke(XInputKeystroke& result) const noexcept = 0;
	};
}
