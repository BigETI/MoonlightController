#define MOONLIGHT_CONTROLLER_LIBRARY
#include <Position.h>

using namespace MoonlightController;

Position::Position() : x(0), y(0)
{
	//
}

Position::Position(const Position & position) : x(position.x), y(position.y)
{
	//
}

Position::Position(int _x, int _y) : x(_x), y(_y)
{
	//
}

Position::~Position()
{
	//
}

Position & Position::operator=(const Position & position)
{
	x = position.x;
	y = position.y;
	return (*this);
}
