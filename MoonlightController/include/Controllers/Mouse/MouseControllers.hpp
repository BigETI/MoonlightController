#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "../../Exportables/Exportable.hxx"
#include "IMouseController.hpp"

namespace MoonlightController::Controllers::Mouse {

	class MouseControllers {
	public:

		MOONLIGHT_CONTROLLER_API MouseControllers();

		MouseControllers(const MouseControllers&) = delete;
		MouseControllers(MouseControllers&&) noexcept = delete;

		MOONLIGHT_CONTROLLER_API static std::size_t GetMaximalControllerCount() noexcept;

		MOONLIGHT_CONTROLLER_API const std::vector<std::shared_ptr<IMouseController>>& GetControllers() const noexcept;

		MOONLIGHT_CONTROLLER_API bool IsControllerAvailable(std::size_t controllerIndex) const noexcept;

		MouseControllers& operator =(const MouseControllers&) = delete;
		MouseControllers& operator =(MouseControllers&&) noexcept = delete;

		MOONLIGHT_CONTROLLER_API const IMouseController& operator [](size_t controllerIndex) const;

	private:

		std::vector<std::shared_ptr<IMouseController>> controllers;
	};
}
