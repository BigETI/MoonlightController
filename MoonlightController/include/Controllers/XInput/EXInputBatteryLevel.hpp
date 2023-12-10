#pragma once

namespace MoonlightController::Controllers::XInput {

	/// <summary>
	/// XInput battery level enumerator
	/// </summary>
	enum class EXInputBatteryLevel {

		/// <summary>
		/// Empty
		/// </summary>
		Empty = 0x0,

		/// <summary>
		/// Low
		/// </summary>
		Low = 0x1,

		/// <summary>
		/// Medium
		/// </summary>
		Medium = 0x2,

		/// <summary>
		/// Full
		/// </summary>
		Full = 0x3
	};
}
