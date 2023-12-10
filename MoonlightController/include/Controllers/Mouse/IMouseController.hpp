#pragma once

#include "../../Position2D.hpp"
#include "EMouseButton.hpp"

namespace MoonlightController::Controllers::Mouse {

	class IMouseController {
	public:

		constexpr virtual ~IMouseController() {
			// ...
		}

		virtual bool IsConnected() const noexcept = 0;

		virtual bool SetCursorPosition(int x, int y) const noexcept = 0;

		virtual bool SetCursorPosition(const Position2D<int>& position) const noexcept = 0;

		virtual bool TryGettingPosition(Position2D<int>& result) const noexcept = 0;

		virtual bool MoveCursor(int x, int y) const noexcept = 0;

		virtual bool MoveCursor(const Vector2D<int>& movement) const noexcept = 0;

		virtual bool ClickButton(EMouseButton button) const noexcept = 0;

		virtual bool PressButton(EMouseButton button) const noexcept = 0;

		virtual bool ReleaseButton(EMouseButton button) const noexcept = 0;

		virtual bool IsButtonDown(EMouseButton button) const noexcept = 0;

		virtual bool ScrollWheel(int scroll) const noexcept = 0;
	};
}
