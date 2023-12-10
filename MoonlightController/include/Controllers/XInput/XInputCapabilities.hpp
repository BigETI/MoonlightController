#pragma once

#include "../../Exportables/Exportable.hxx"
#include "EXInputDeviceType.hpp"
#include "EXInputDeviceSubType.hpp"
#include "EXInputDeviceFeatures.hpp"
#include "EXInputButtons.hpp"

namespace MoonlightController::Controllers::XInput {

	struct XInputCapabilities {
	public:

		/// <summary>
		/// Device type
		/// </summary>
		EXInputDeviceType deviceType;

		/// <summary>
		/// Device subtype
		/// </summary>
		EXInputDeviceSubType deviceSubType;

		/// <summary>
		/// Device features
		/// </summary>
		EXInputDeviceFeatures deviceFeatures;

		/// <summary>
		/// Buttons
		/// </summary>
		EXInputButtons buttons;

		/// <summary>
		/// Left trigger
		/// </summary>
		float leftTrigger;

		/// <summary>
		/// Right trigger
		/// </summary>
		float rightTrigger;

		/// <summary>
		/// Thumb LX
		/// </summary>
		float thumbLX;

		/// <summary>
		/// Thumb LY
		/// </summary>
		float thumbLY;

		/// <summary>
		/// Thumb RX
		/// </summary>
		float thumbRX;

		/// <summary>
		/// Thumb RY
		/// </summary>
		float thumbRY;

		/// <summary>
		/// Left motor
		/// </summary>
		float leftMotor;

		/// <summary>
		/// Right motor
		/// </summary>
		float rightMotor;

		MOONLIGHT_CONTROLLER_API XInputCapabilities();

		MOONLIGHT_CONTROLLER_API XInputCapabilities(
			EXInputDeviceType deviceType,
			EXInputDeviceSubType deviceSubType,
			EXInputDeviceFeatures deviceFeatures,
			EXInputButtons buttons,
			float leftTrigger,
			float rightTrigger,
			float thumbLX,
			float thumbLY,
			float thumbRX,
			float thumbRY,
			float leftMotor,
			float rightMotor
		);
	};
}
