#ifndef __MOONLIGHT_CONTROLLER_EVENT_SYSTEM_H__
#	define __MOONLIGHT_CONTROLLER_EVENT_SYSTEM_H__
#	include <vector>

// Moonlight controller namespace
namespace MoonlightController
{
	// Event system class
	template < class _R, class _T > class EventSystem
	{
	private:
		// Functions
		std::vector<typename _R(*)(typename _T)> functions;
	public:
		// Default constructor
		EventSystem()
		{
			//
		}

		// Destructor
		~EventSystem()
		{
			functions.clear();
		}

		// Register
		void Register(typename _R(*function)(typename _T))
		{
			functions.push_back(function);
		}

		// Invoke
		std::vector<typename _R> Invoke(typename _T arguments)
		{
			std::vector<typename _R> ret;
			for (typename _R(*function)(typename _T) : functions)
			{
				ret.push_back(function(arguments));
			}
			return ret;
		}
	};
}
#endif
