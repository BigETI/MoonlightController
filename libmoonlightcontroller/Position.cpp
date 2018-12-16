#define MOONLIGHT_CONTROLLER_LIBRARY
#include <libmoonlightcontroller/Position.h>

using namespace MoonlightController;

/// <summary>
/// Default constructor
/// </summary>
Position::Position() : x(0), y(0)
{
	//
}

/// <summary>
/// Copy constructor
/// </summary>
/// <param name="position">Position</param>
Position::Position(const Position & position) : x(position.x), y(position.y)
{
	//
}

/// <summary>
/// Constructor
/// </summary>
/// <param name="x">X</param>
/// <param name="y">Y</param>
Position::Position(int x, int y) : x(x), y(y)
{
	//
}

/// <summary>
/// Destructor
/// </summary>
Position::~Position()
{
	//
}

/// <summary>
/// Assign operator
/// </summary>
/// <param name="position">Position</param>
/// <returns>This</returns>
Position & Position::operator = (const Position & position)
{
	x = position.x;
	y = position.y;
	return (*this);
}
