#pragma once

#include "../../Exportables/Exportable.hxx"
#include "EXInputVirtualKey.hpp"
#include "EXInputKeyboardStates.hpp"

namespace MoonlightController::Controllers::XInput {

	struct XInputKeystroke {

		/// <summary>
		/// Virtual key
		/// </summary>
		EXInputVirtualKey virtualKey;

		/// <summary>
		/// Unicode
		/// </summary>
		wchar_t unicode;

		/// <summary>
		/// Keyboard states
		/// </summary>
		EXInputKeyboardStates keyboardStates;

		/// <summary>
		/// User index
		/// </summary>
		int userIndex;

		/// <summary>
		/// HID code
		/// </summary>
		unsigned char hidCode;

		MOONLIGHT_CONTROLLER_API XInputKeystroke();

		MOONLIGHT_CONTROLLER_API XInputKeystroke(EXInputVirtualKey virtualKey, wchar_t unicode, EXInputKeyboardStates keyboardStates, int userIndex, unsigned char hidCode);
	};
}
