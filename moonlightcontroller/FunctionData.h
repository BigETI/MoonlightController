#ifndef __FUNCTION_DATA_H__
#	define __FUNCTION_DATA_H__

#	include <string>
#	include <vector>

// Function data structure
struct FunctionData
{
	// Function
	bool(*function)(std::vector<std::string> &);

	// Help string
	std::string help;

	// Is unique
	bool isUnique;

	// Constructor
	FunctionData(bool(*_function)(std::vector<std::string> &), std::string _help, bool _isUnique) : function(_function), help(_help), isUnique(_isUnique)
	{
		//
	}
};
#endif
