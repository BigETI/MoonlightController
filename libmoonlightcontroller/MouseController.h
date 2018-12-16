#ifndef __MOONLIGHT_CONTROLLER_MOUSE_CONTROLLER_H__
#	define __MOONLIGHT_CONTROLLER_MOUSE_CONTROLLER_H__

#	include <libmoonlightcontroller/Position.h>
#	include <libmoonlightcontroller/EMouseButton.h>
#	include <libmoonlightcontroller/Platform.h>

#	if defined(MOONLIGHT_CONTROLLER_LINUX)
#		include <libmoonlightcontroller/Linux/UserInputOutput.h>
#	endif

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// Mouse controller class
	/// </summary>
	class MouseController
	{
	private:

#if defined(MOONLIGHT_CONTROLLER_LINUX)

		/// <summary>
		/// User input output
		/// </summary>
		UserInputOutput userInputOutput;

#endif

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="">Mouse controller</param>
		MouseController(const MouseController &);

		/// <summary>
		/// Assign operator
		/// </summary>
		/// <param name="">Mouse controller</param>
		/// <returns>This</returns>
		MouseController & operator = (const MouseController &);

	public:

		/// <summary>
		/// Default constructor
		/// </summary>
		MouseController();

		/// <summary>
		/// Destructor
		/// </summary>
		~MouseController();

		/// <summary>
		/// Set mouse position
		/// </summary>
		/// <param name="x">Mouse X</param>
		/// <param name="y">Mouse Y</param>
		void SetPosition(int x, int y);

		/// <summary>
		/// Get mouse position
		/// </summary>
		/// <param name="position">Mouse position</param>
		/// <returns>Mouse position</returns>
		Position & GetPosition(Position & position);

		/// <summary>
		/// Move mouse (relative)
		/// </summary>
		/// <param name="x">Mouse X</param>
		/// <param name="y">Mouse Y</param>
		void Move(int x, int y);

		/// <summary>
		/// Mouse click
		/// </summary>
		/// <param name="mouseButton">Mouse button</param>
		void Click(EMouseButton button);

		/// <summary>
		/// Mouse press
		/// </summary>
		/// <param name="button">Mouse button</param>
		/// <param name="down">Press down</param>
		void Press(EMouseButton button, bool down);

		/// <summary>
		/// Is mouse down
		/// </summary>
		/// <param name="button">Mouse button</param>
		/// <returns>"true" if mouse button is down, otherwise "false"</returns>
		bool IsDown(EMouseButton button);

		/// <summary>
		/// Scroll mouse wheel
		/// </summary>
		/// <param name="scroll">Scroll</param>
		void Scroll(int scroll);
	};
}
#endif
