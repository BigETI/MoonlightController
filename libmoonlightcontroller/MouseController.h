#ifndef __MOONLIGHT_CONTROLLER_MOUSE_CONTROLLER_H__
#	define __MOONLIGHT_CONTROLLER_MOUSE_CONTROLLER_H__
#	include <Position.h>
#	include <EMouseButton.h>
// Moonlight controller namespace
namespace MoonlightController
{
	// Mouse controller class
	class MouseController
	{
	private:
		// Default constructor
		MouseController();

		// Copy constructor
		MouseController(const MouseController &);

		// Assign operator
		MouseController & operator = (const MouseController &);
	public:
		// Set mouse position
		static void SetPosition(int x, int y);

		// Get mouse position
		static Position GetPosition();

		// Move mouse (relative)
		static void Move(int x, int y);

		// Mouse click
		static void Click(EMouseButton mouseButton);

		// Mouse press
		static void Press(EMouseButton mouseButton, bool down);

		// Is mouse down
		static bool IsDown(EMouseButton mouseButton);

		// Scroll mouse wheel
		static void Scroll(int scroll);
	};
}
#endif
