#ifndef __MOONLIGHT_CONTROLLER_MOUSE_CONTROLLER_H__
#	define __MOONLIGHT_CONTROLLER_MOUSE_CONTROLLER_H__

#	include <libmoonlightcontroller/Position.h>
#	include <libmoonlightcontroller/EMouseButton.h>
#	include <libmoonlightcontroller/Platform.h>

#	if defined(MOONLIGHT_CONTROLLER_LINUX)
#		include <libmoonlightcontroller/Linux/UserInputOutput.h>
#	endif

// Moonlight controller namespace
namespace MoonlightController
{
	// Mouse controller class
	class MouseController
	{
	private:
		
		#if defined(MOONLIGHT_CONTROLLER_LINUX)
		
		// User input output
		UserInputOutput userInputOutput;

		#endif

		// Copy constructor
		MouseController(const MouseController &);

		// Assign operator
		MouseController & operator = (const MouseController &);

	public:

		// Default constructor
		MouseController();

		// Destructor
		~MouseController();

		// Set mouse position
		void SetPosition(int x, int y);

		// Get mouse position
		Position GetPosition();

		// Move mouse (relative)
		void Move(int x, int y);

		// Mouse click
		void Click(EMouseButton mouseButton);

		// Mouse press
		void Press(EMouseButton mouseButton, bool down);

		// Is mouse down
		bool IsDown(EMouseButton mouseButton);

		// Scroll mouse wheel
		void Scroll(int scroll);
	};
}
#endif
