#pragma once

#include "../../../../Controllers/Mouse/IMouseController.hpp"
#include "../../../../Controllers/Mouse/EMouseButton.hpp"
#include "../../../../Exportables/Exportable.hxx"
#include "../../../../Position2D.hpp"
#include "../../../../Vector2D.hpp"

namespace MoonlightController::Platforms::Windows::Controllers::Mouse {

	class MouseController : public MoonlightController::Controllers::Mouse::IMouseController {
	public:

		MOONLIGHT_CONTROLLER_API MouseController();

		MOONLIGHT_CONTROLLER_API MouseController(const MouseController& mouseController);

		MOONLIGHT_CONTROLLER_API MouseController(MouseController&& mouseController) noexcept;

		MOONLIGHT_CONTROLLER_API bool IsConnected() const noexcept override;

		MOONLIGHT_CONTROLLER_API bool SetCursorPosition(int x, int y) const noexcept override;
		
		MOONLIGHT_CONTROLLER_API bool SetCursorPosition(const Position2D<int>& position) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool TryGettingPosition(Position2D<int>& result) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool MoveCursor(int x, int y) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool MoveCursor(const Vector2D<int>& movement) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool ClickButton(MoonlightController::Controllers::Mouse::EMouseButton button) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool PressButton(MoonlightController::Controllers::Mouse::EMouseButton button) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool ReleaseButton(MoonlightController::Controllers::Mouse::EMouseButton button) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool IsButtonDown(MoonlightController::Controllers::Mouse::EMouseButton button) const noexcept override;

		MOONLIGHT_CONTROLLER_API bool ScrollWheel(int scroll) const noexcept override;

		MOONLIGHT_CONTROLLER_API MouseController& operator =(const MouseController& mouseController);

		MOONLIGHT_CONTROLLER_API MouseController& operator =(MouseController&& mouseController) noexcept;
	};
}
