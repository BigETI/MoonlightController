#pragma once

#include <string_view>

#include "../../../../Controllers/Keyboard/IKeyboardController.hpp"
#include "../../../../Exportables/Exportable.hxx"

namespace MoonlightController::Platforms::Windows::Controllers::Keyboard {

	class KeyboardController : public MoonlightController::Controllers::Keyboard::IKeyboardController {
	public:

		MOONLIGHT_CONTROLLER_API KeyboardController();

		KeyboardController(const KeyboardController& keyboardController);

		KeyboardController(KeyboardController&& keyboardController) noexcept;

		MOONLIGHT_CONTROLLER_API bool ClickKey(int keyCode) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool PressKey(int keyCode) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool ReleaseKey(int keyCode) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool IsKeyDown(int keyCode) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool AppendTextAsKeystrokes(std::string_view textAsInput) const noexcept override;

		MOONLIGHT_CONTROLLER_API KeyboardController& operator =(const KeyboardController& keyboardController);

		MOONLIGHT_CONTROLLER_API KeyboardController& operator =(KeyboardController&& keyboardController) noexcept;
	};
}
