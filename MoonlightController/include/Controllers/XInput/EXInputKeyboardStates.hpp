#pragma once

#include <type_traits>

namespace MoonlightController::Controllers::XInput {

	/// <summary>
	/// XInput keyboard states enumerator
	/// </summary>
	enum class EXInputKeyboardStates {

		/// <summary>
		/// Key down
		/// </summary>
		KeyDown = 0x1,

		/// <summary>
		/// Key up
		/// </summary>
		KeyUp = 0x2,

		/// <summary>
		/// Repeat
		/// </summary>
		Repeat = 0x4
	};

	constexpr inline static EXInputKeyboardStates operator &(EXInputKeyboardStates left, EXInputKeyboardStates right) {
		return EXInputKeyboardStates(std::underlying_type<EXInputKeyboardStates>::type(left) & std::underlying_type<EXInputKeyboardStates>::type(right));
	}

	constexpr inline static EXInputKeyboardStates operator |(EXInputKeyboardStates left, EXInputKeyboardStates right) {
		return EXInputKeyboardStates(std::underlying_type<EXInputKeyboardStates>::type(left) | std::underlying_type<EXInputKeyboardStates>::type(right));
	}

	constexpr inline static EXInputKeyboardStates operator ^(EXInputKeyboardStates left, EXInputKeyboardStates right) {
		return EXInputKeyboardStates(std::underlying_type<EXInputKeyboardStates>::type(left) ^ std::underlying_type<EXInputKeyboardStates>::type(right));
	}
}
