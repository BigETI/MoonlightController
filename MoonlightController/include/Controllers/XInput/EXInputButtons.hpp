#pragma once

namespace MoonlightController::Controllers::XInput {

	/// <summary>
	/// XInput buttons enumerator
	/// </summary>
	enum class EXInputButtons {

		/// <summary>
		/// D-Pad up
		/// </summary>
		DPadUp = 0x1,

		/// <summary>
		/// D-Pad down
		/// </summary>
		DPadDown = 0x2,

		/// <summary>
		/// D-Pad left
		/// </summary>
		DPadLeft = 0x4,

		/// <summary>
		/// D-Pad right
		/// </summary>
		DPadRight = 0x8,

		/// <summary>
		/// Start
		/// </summary>
		Start = 0x10,

		/// <summary>
		/// Back
		/// </summary>
		Back = 0x20,

		/// <summary>
		/// Left thumb
		/// </summary>
		LeftThumb = 0x40,

		/// <summary>
		/// Right thumb
		/// </summary>
		RightThumb = 0x80,

		/// <summary>
		/// Left shoulder
		/// </summary>
		LeftShoulder = 0x100,

		/// <summary>
		/// Right shoulder
		/// </summary>
		RightShoulder = 0x200,

		/// <summary>
		/// A
		/// </summary>
		A = 0x1000,

		/// <summary>
		/// B
		/// </summary>
		B = 0x2000,

		/// <summary>
		/// X
		/// </summary>
		X = 0x4000,

		/// <summary>
		/// Y
		/// </summary>
		Y = 0x8000
	};
}
