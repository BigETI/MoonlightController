#ifndef __MOONLIGHT_CONTROLLER_E_XINPUT_DEVICE_FEATURES_H__
#	define __MOONLIGHT_CONTROLLER_E_XINPUT_DEVICE_FEATURES_H__

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// XInput device features enumerator
	/// </summary>
	enum EXInputDeviceFeatures
	{
		/// <summary>
		/// Force feedback supported
		/// </summary>
		EXInputDeviceFeatures_FFBSupported = 0x1,

		/// <summary>
		/// Wireless
		/// </summary>
		EXInputDeviceFeatures_Wireless = 0x2,

		/// <summary>
		/// Voice supported
		/// </summary>
		EXInputDeviceFeatures_VoiceSupported = 0x4,

		/// <summary>
		/// Plug-in modules supported
		/// </summary>
		EXInputDeviceFeatures_PMDSupported = 0x8,

		/// <summary>
		/// No navigation buttons
		/// </summary>
		EXInputDeviceFeatures_NoNavigation = 0x10
	};
}
#endif
