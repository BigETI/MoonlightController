#ifndef __FUNCTION_DATA_H__
#	define __FUNCTION_DATA_H__
#	include <string>
#	include <vector>
struct FunctionData
{
	typename bool(*function)(std::vector<std::string> &);
	std::string help;
	bool isUnique;
	FunctionData(bool(*_function)(std::vector<std::string> &), std::string _help, bool _isUnique) : function(_function), help(_help), isUnique(_isUnique)
	{
		//
	}
};
#endif
