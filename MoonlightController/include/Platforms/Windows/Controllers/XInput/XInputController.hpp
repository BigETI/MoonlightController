#pragma once

#include <cstddef>
#include <string>

#include "../../../../Exportables/Exportable.hxx"
#include "../../../../Controllers/XInput/EXInputBatteryDeviceType.hpp"
#include "../../../../Controllers/XInput/EXInputButtons.hpp"
#include "../../../../Controllers/XInput/EXInputAxis.hpp"
#include "../../../../Controllers/XInput/IXInputController.hpp"
#include "../../../../Controllers/XInput/XInputBatteryInformation.hpp"
#include "../../../../Controllers/XInput/XInputCapabilities.hpp"
#include "../../../../Controllers/XInput/XInputKeystroke.hpp"

namespace MoonlightController::Platforms::Windows::Controllers::XInput {
	class XInputController : public MoonlightController::Controllers::XInput::IXInputController {
	public:

		XInputController() = delete;

		MOONLIGHT_CONTROLLER_API XInputController(const XInputController& xInputController);
		
		MOONLIGHT_CONTROLLER_API XInputController(XInputController&& xInputController) noexcept;

		MOONLIGHT_CONTROLLER_API XInputController(std::size_t index);

		MOONLIGHT_CONTROLLER_API std::size_t GetIndex() const noexcept override;

		MOONLIGHT_CONTROLLER_API bool IsConnected() const noexcept override;

		MOONLIGHT_CONTROLLER_API bool TryGettingPressedButtons(MoonlightController::Controllers::XInput::EXInputButtons& result) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool TryGettingAxisValue(MoonlightController::Controllers::XInput::EXInputAxis axis, float& result) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool SetVibration(float leftMotor, float rightMotor) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool TryGettingAudioDeviceIDs(std::wstring& outRenderDeviceID, std::wstring& outCaptureDeviceID) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool TryGettingBatteryInformation(
			MoonlightController::Controllers::XInput::EXInputBatteryDeviceType batteryDeviceType,
			MoonlightController::Controllers::XInput::XInputBatteryInformation& result
		) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool TryGettingCapabilities(MoonlightController::Controllers::XInput::XInputCapabilities& result) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool TryGettingKeystroke(MoonlightController::Controllers::XInput::XInputKeystroke& result) const noexcept override;

		MOONLIGHT_CONTROLLER_API XInputController& operator =(const XInputController& xInputController);

		MOONLIGHT_CONTROLLER_API XInputController& operator =(XInputController&& xInputController) noexcept;

	private:

		std::size_t index;
	};
}
