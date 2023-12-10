#pragma once

#include <type_traits>

namespace MoonlightController::Controllers::XInput {

	/// <summary>
	/// XInput device features enumerator
	/// </summary>
	enum class EXInputDeviceFeatures {

		/// <summary>
		/// Force feedback supported
		/// </summary>
		FFBSupported = 0x1,

		/// <summary>
		/// Wireless
		/// </summary>
		Wireless = 0x2,

		/// <summary>
		/// Voice supported
		/// </summary>
		VoiceSupported = 0x4,

		/// <summary>
		/// Plug-in modules supported
		/// </summary>
		PMDSupported = 0x8,

		/// <summary>
		/// No navigation buttons
		/// </summary>
		NoNavigation = 0x10
	};

	constexpr inline static EXInputDeviceFeatures operator &(EXInputDeviceFeatures left, EXInputDeviceFeatures right) {
		return EXInputDeviceFeatures(std::underlying_type<EXInputDeviceFeatures>::type(left) & std::underlying_type<EXInputDeviceFeatures>::type(right));
	}

	constexpr inline static EXInputDeviceFeatures operator |(EXInputDeviceFeatures left, EXInputDeviceFeatures right) {
		return EXInputDeviceFeatures(std::underlying_type<EXInputDeviceFeatures>::type(left) | std::underlying_type<EXInputDeviceFeatures>::type(right));
	}

	constexpr inline static EXInputDeviceFeatures operator ^(EXInputDeviceFeatures left, EXInputDeviceFeatures right) {
		return EXInputDeviceFeatures(std::underlying_type<EXInputDeviceFeatures>::type(left) ^ std::underlying_type<EXInputDeviceFeatures>::type(right));
	}
}
