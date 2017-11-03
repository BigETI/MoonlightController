#ifndef __MOONLIGHT_CONTROLLER_E_XINPUT_DEVICE_FEATURES_H__
#	define __MOONLIGHT_CONTROLLER_E_XINPUT_DEVICE_FEATURES_H__

// Moonlight controller namespace
namespace MoonlightController
{
	// XInput device features enumerator
	enum EXInputDeviceFeatures
	{
		// Force feedback supported
		EXInputDeviceFeatures_FFBSupported = 0x1,

		// Wireless
		EXInputDeviceFeatures_Wireless = 0x2,

		// Voice supported
		EXInputDeviceFeatures_VoiceSupported = 0x4,

		// Plug-in modules supported
		EXInputDeviceFeatures_PMDSupported = 0x8,

		// No navigation buttons
		EXInputDeviceFeatures_NoNavigation = 0x10
	};
}
#endif
