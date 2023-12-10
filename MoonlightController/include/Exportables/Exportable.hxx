#pragma once

#if defined(IS_MOONLIGHT_CONTROLLER_STATIC)
#	define MOONLIGHT_CONTROLLER_API
#elif defined(_MSC_VER)
#	if IS_MOONLIGHT_CONTROLLER_EXPORTING
#		define MOONLIGHT_CONTROLLER_API __declspec(dllexport)
#	else
#		define MOONLIGHT_CONTROLLER_API __declspec(dllimport)
#	endif
#elif defined(__GNUC__)
#	if IS_MOONLIGHT_CONTROLLER_EXPORTING
#		define MOONLIGHT_CONTROLLER_API __attribute__((visibility("default")))
#	else
#		define MOONLIGHT_CONTROLLER_API
#	endif
#else
#	define MOONLIGHT_CONTROLLER_API
#	if IS_MOONLIGHT_CONTROLLER_EXPORTING
#		pragma warning Unknown dynamic link export semantic.
#	else
#		pragma warning Unknown dynamic link import semantic.
#	endif
#endif
