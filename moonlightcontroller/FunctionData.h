#ifndef __FUNCTION_DATA_H__
#	define __FUNCTION_DATA_H__

#	include <string>
#	include <vector>

/// <summary>
/// Function data structure
/// </summary>
struct FunctionData
{
	/// <summary>
	/// Function
	/// </summary>
	bool(*function)(const std::vector<std::string> &);

	/// <summary>
	/// Help string
	/// </summary>
	std::string help;

	/// <summary>
	/// Is unique
	/// </summary>
	bool isUnique;

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="function">Function</param>
	/// <param name="help">Help</param>
	/// <param name="isUnique">Is unique</param>
	FunctionData(bool(*function)(const std::vector<std::string> &), const std::string & help, bool isUnique) : function(function), help(help), isUnique(isUnique)
	{
		//
	}
};
#endif
