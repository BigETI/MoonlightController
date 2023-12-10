#pragma once

namespace MoonlightController::Controllers::XInput {

	/// <summary>
	/// XInput battery type enumerator
	/// </summary>
	enum class EXInputBatteryType {

		/// <summary>
		/// Disconnected
		/// </summary>
		Disconnected = 0x0,

		/// <summary>
		/// Wired
		/// </summary>
		Wired = 0x1,

		/// <summary>
		/// Alkaline
		/// </summary>
		Alkaline = 0x2,

		/// <summary>
		/// Nickel metal hybrid
		/// </summary>
		NiMH = 0x3,

		/// <summary>
		/// Unknown
		/// </summary>
		Unknown = 0xFF
	};
}
