#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "../../Exportables/Exportable.hxx"
#include "IKeyboardController.hpp"

namespace MoonlightController::Controllers::Keyboard {

	class KeyboardControllers {
	public:

		MOONLIGHT_CONTROLLER_API KeyboardControllers();

		KeyboardControllers(const KeyboardControllers&) = delete;
		KeyboardControllers(KeyboardControllers&&) noexcept = delete;

		MOONLIGHT_CONTROLLER_API static std::size_t GetMaximalControllerCount() noexcept;

		MOONLIGHT_CONTROLLER_API const std::vector<std::shared_ptr<IKeyboardController>>& GetControllers() const noexcept;

		MOONLIGHT_CONTROLLER_API bool IsControllerAvailable(std::size_t controllerIndex) const noexcept;

		KeyboardControllers& operator =(const KeyboardControllers&) = delete;
		KeyboardControllers& operator =(KeyboardControllers&&) noexcept = delete;

		MOONLIGHT_CONTROLLER_API const IKeyboardController& operator [](size_t controllerIndex) const;

	private:

		std::vector<std::shared_ptr<IKeyboardController>> controllers;
	};
}
