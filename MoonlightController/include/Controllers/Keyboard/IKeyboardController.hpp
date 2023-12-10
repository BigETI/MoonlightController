#pragma once

#include <string_view>

namespace MoonlightController::Controllers::Keyboard {
	class IKeyboardController {
	public:

		constexpr virtual ~IKeyboardController() {
			// ...
		}

		virtual bool ClickKey(int keyCode) const noexcept = 0;

		virtual bool PressKey(int keyCode) const noexcept = 0;

		virtual bool ReleaseKey(int keyCode) const noexcept = 0;

		virtual bool IsKeyDown(int keyCode) const noexcept = 0;

		virtual bool AppendTextAsKeystrokes(std::string_view textAsInput) const noexcept = 0;
	};
}
