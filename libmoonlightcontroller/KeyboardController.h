#ifndef __MOONLIGHT_CONTROLLER_KEYBOARD_CONTROLLER_H__
#	define __MOONLIGHT_CONTROLLER_KEYBOARD_CONTROLLER_H__

#	include <libmoonlightcontroller/Platform.h>
#	include <set>
#	include <string>

#	if defined(MOONLIGHT_CONTROLLER_LINUX)
#		include <libmoonlightcontroller/Linux/UserInputOutput.h>
#	endif

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// Keybaord controller class
	/// </summary>
	class KeyboardController
	{
	private:

		#if defined(MOONLIGHT_CONTROLLER_LINUX)

		/// <summary>
		/// User input
		/// </summary>
		UserInputOutput userInputOutput;

		#endif

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="">Keyboard controller</param>
		KeyboardController(const KeyboardController &);

		/// <summary>
		/// Assign operator
		/// </summary>
		/// <param name="">Keyboard controller</param>
		/// <returns>This</returns>
		KeyboardController & operator = (const KeyboardController &);

	public:

		/// <summary>
		/// Default constructor
		/// </summary>
		KeyboardController();

		/// <summary>
		/// Destructor
		/// </summary>
		~KeyboardController();

		/// <summary>
		/// Click keyboard key
		/// </summary>
		/// <param name="key">Key code</param>
		void Click(int keyCode);

		/// <summary>
		/// Press keyboard key
		/// </summary>
		/// <param name="key">Key code</param>
		/// <param name="down">Press down</param>
		void Press(int keyCode, bool down);

		/// <summary>
		/// Is keyboard key down
		/// </summary>
		/// <param name="keyCode">Key code</param>
		/// <returns>"true" if keyboard key is down, otherwise "false"</returns>
		bool IsDown(int keyCode);

		/// <summary>
		/// Text input
		/// </summary>
		/// <param name="input">Text input</param>
		void Input(const std::string & input);
	};
}
#endif
