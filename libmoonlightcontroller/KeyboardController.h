#ifndef __MOONLIGHT_CONTROLLER_KEYBOARD_CONTROLLER_H__
#	define __MOONLIGHT_CONTROLLER_KEYBOARD_CONTROLLER_H__

#	include <libmoonlightcontroller/Platform.h>
#	include <string>

#	if defined(MOONLIGHT_CONTROLLER_LINUX)
#		include <libmoonlightcontroller/Linux/UserInputOutput.h>
#	endif

// Moonlight controller namespace
namespace MoonlightController
{
	// Keyboard controller class
	class KeyboardController
	{
	private:

		#if defined(MOONLIGHT_CONTROLLER_LINUX)

		// User input
		UserInputOutput userInputOutput;

		#endif

		// Copy constructor
		KeyboardController(const KeyboardController &);

		// Assign operator
		KeyboardController & operator = (const KeyboardController &);

	public:

		// Default constructor
		KeyboardController();

		// Destructor
		~KeyboardController();

		// Click key
		void Click(int key);

		// Press key
		void Press(int key, bool down);

		// Is key down
		bool IsDown(int key);

		// Text input
		void Input(std::string input);
	};
}
#endif
