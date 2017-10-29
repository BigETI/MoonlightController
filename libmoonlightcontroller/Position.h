#ifndef __MOONLIGHT_CONTROLLER_POSITION_H__
#	define __MOONLIGHT_CONTROLLER_POSITION_H__
// Moonlight controller namespace
namespace MoonlightController
{
	// Position class
	class Position
	{
	public:
		// X
		int x;

		// Y
		int y;

		// Default constructor
		Position();

		// Copy constructor
		Position(const Position &position);

		// Constructor
		Position(int _x, int _y);

		// Destructor
		~Position();

		// Assign operator
		Position &operator=(const Position &position);
	};
}
#endif
