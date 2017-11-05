#ifndef __MOONLIGHT_CONTROLLER_PLATFORM_H__
#	define __MOONLIGHT_CONTROLLER_PLATFORM_H__
#	ifndef __cplusplus
#		error Please compile this with a C++ compiler
#	endif
#	if defined(__linux__) || defined(__unix__)
#		define MOONLIGHT_CONTROLLER_LINUX
#	elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)|| defined(__WIN64__) || defined(WIN64) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__MINGW64__) || defined(__BORLANDC__)
#		define MOONLIGHT_CONTROLLER_WINDOWS
#		include <Windows.h>
#	elif defined(__APPLE__)
#		define MOONLIGHT_CONTROLLER_OSX
#	endif
#endif
