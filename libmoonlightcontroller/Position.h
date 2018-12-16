#ifndef __MOONLIGHT_CONTROLLER_POSITION_H__
#	define __MOONLIGHT_CONTROLLER_POSITION_H__

/// <summary>
/// Moonlight controller namespace
/// </summary>
namespace MoonlightController
{
	/// <summary>
	/// Position class
	/// </summary>
	class Position
	{
	public:
		/// <summary>
		/// X
		/// </summary>
		int x;

		/// <summary>
		/// Y
		/// </summary>
		int y;

		/// <summary>
		/// Default constructor
		/// </summary>
		Position();

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="position">Position</param>
		Position(const Position & position);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="x">X</param>
		/// <param name="y">Y</param>
		Position(int x, int y);

		/// <summary>
		/// Destructor
		/// </summary>
		~Position();

		/// <summary>
		/// Assign operator
		/// </summary>
		/// <param name="position">Position</param>
		/// <returns>This</returns>
		Position & operator = (const Position & position);
	};
}
#endif
