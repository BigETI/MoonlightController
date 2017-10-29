#ifndef __MOONLIGHT_CONTROLLER_KEYBOARD_CONTROLLER_H__
#	define __MOONLIGHT_CONTROLLER_KEYBOARD_CONTROLLER_H__
#	include <string>
// Moonlight controller namespace
namespace MoonlightController
{
	// Keyboard controller class
	class KeyboardController
	{
	private:
		// Default constructor
		KeyboardController();

		// Copy constructor
		KeyboardController(const KeyboardController &);

		// Assign operator
		KeyboardController & operator = (const KeyboardController &);
	public:
		// Click key
		static void Click(int key);

		// Press key
		static void Press(int key, bool down);

		// Is key down
		static bool IsDown(int key);

		// Text input
		static void Input(std::string input);
	};
}
#endif
