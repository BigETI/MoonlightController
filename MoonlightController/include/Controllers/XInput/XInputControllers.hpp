#pragma once

#include <memory>
#include <vector>

#include "../../Exportables/Exportable.hxx"
#include "IXInputController.hpp"

namespace MoonlightController::Controllers::XInput {

	class XInputControllers {
	public:

		MOONLIGHT_CONTROLLER_API XInputControllers();

		XInputControllers(const XInputControllers&) = delete;
		XInputControllers(XInputControllers&&) noexcept = delete;

		MOONLIGHT_CONTROLLER_API static std::size_t GetMaximalControllerCount() noexcept;

		MOONLIGHT_CONTROLLER_API const std::vector<std::shared_ptr<IXInputController>>& GetControllers() const noexcept;
		
		MOONLIGHT_CONTROLLER_API bool IsControllerAvailable(std::size_t controllerIndex) const noexcept;
		
		XInputControllers& operator =(const XInputControllers&) = delete;
		XInputControllers& operator =(XInputControllers&&) noexcept = delete;

		MOONLIGHT_CONTROLLER_API const IXInputController& operator [](size_t controllerIndex) const;

	private:

		std::vector<std::shared_ptr<IXInputController>> controllers;
	};
}
