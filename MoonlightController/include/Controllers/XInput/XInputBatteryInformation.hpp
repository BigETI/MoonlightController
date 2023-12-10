#pragma once

#include "../../Exportables/Exportable.hxx"
#include "EXInputBatteryType.hpp"
#include "EXInputBatteryLevel.hpp"

namespace MoonlightController::Controllers::XInput {

	struct XInputBatteryInformation {
	public:

		/// <summary>
		/// Battery type
		/// </summary>
		EXInputBatteryType batteryType;

		/// <summary>
		/// Battery level
		/// </summary>
		EXInputBatteryLevel batteryLevel;

		MOONLIGHT_CONTROLLER_API XInputBatteryInformation();

		MOONLIGHT_CONTROLLER_API XInputBatteryInformation(EXInputBatteryType batteryType, EXInputBatteryLevel batteryLevel);
	};
}
