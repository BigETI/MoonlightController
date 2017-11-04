#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <libmoonlightcontroller/LuaModule.h>
#include <FunctionData.h>
#include <libmoonlightcontroller/Platform.h>

using namespace MoonlightController;
using namespace std;
using namespace std::chrono;

// Libraries
static ELuaModuleLibraries libraries(ELuaModuleLibraries_Recommended);

// Render help
static bool RenderHelp(vector<string> & args);

// Add modules
static bool AddModules(vector<string> & args);

// Change libraries
static bool ChangeLibraries(vector<string> & args);

// Modules
static map<string, LuaModule *> modules;

// Arguments
static map<string, FunctionData> argumentFunctions =
{
	{ "-h", { RenderHelp, "Shows this help topic", true } },
	{ "--help", { RenderHelp, "", false } },
	{ "-m", { AddModules, "Add Lua modules to load", true } },
	{ "--modules",{ AddModules, "", false } },
	{ "-l", { ChangeLibraries, "Change the required Lua libraries", true } },
	{ "--libraries", { ChangeLibraries, "", false } }
};

// File exists
inline bool FileExists(const string & name)
{
#if defined(MOONLIGHT_CONTROLLER_LINUX)
	bool ret(false);
	FILE *f(fopen(name.c_str(), "rb"));
	if (f)
	{
		ret = true;
		fclose(f);
	}
	return ret;
#elif defined(MOONLIGHT_CONTROLLER_WINDOWS)
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
#endif
}

// Clear modules
inline void ClearModules()
{
	for (pair<string, LuaModule *> module : modules)
	{
		delete module.second;
	}
	modules.clear();
}

// Render help
static bool RenderHelp(vector<string> & args)
{
	cout << "Moonlight controller help:" << endl;
	for (pair<string, FunctionData> function : argumentFunctions)
	{
		if (function.second.isUnique)
		{
			cout << "\t" << function.first << endl << "\t\t" << function.second.help << endl;
		}
	}
	cout << "End of help topic" << endl;
	return false;
}

// Add modules
static bool AddModules(vector<string> & args)
{
	bool ret(false);
	map<string, LuaModule *>::iterator it, end(modules.end());
	LuaModule *module;
	if (args.size() > 0)
	{
		ret = true;
		for (string arg : args)
		{
			it = modules.find(arg);
			if (it == modules.end())
			{
				try
				{
					module = new LuaModule(arg, true, libraries);
					if (module)
					{
						if (module->IsActive())
						{
							modules[arg] = module;
						}
						else
						{
							delete module;
						}
					}
					else
					{
						break;
					}
				}
				catch (exception e)
				{
					cerr << e.what() << endl;
					break;
				}
				catch (...)
				{
					cerr << "A fatal error has occured." << endl;
					break;
				}
				end = modules.end();
			}
		}
	}
	return ret;
}

// Change libraries
static bool ChangeLibraries(vector<string> & args)
{
	bool ret(false);
	if (args.size() == 1)
	{
		ret = true;
		libraries = static_cast<ELuaModuleLibraries>(std::stoi(args[0]));
	}
	return ret;
}

// Main entry point (platform independent)
int Main(string & fileName, vector<string> & arguments)
{
	string arg;
	vector<string> args;
	map<string, FunctionData>::iterator it, end(argumentFunctions.end());
	for (size_t i(0U); i < arguments.size(); i++)
	{
		arg = arguments[i];
		if (arg[0] == '-')
		{
			it = argumentFunctions.find(arg);
			if (it == end)
			{
				ClearModules();
				RenderHelp(args);
				break;
			}
			else
			{
				string s_arg;
				bool end_reached(true);
				for (size_t j(i + 1U); j < arguments.size(); j++)
				{
					s_arg = arguments[j];
					if (s_arg[0] == '-')
					{
						i = j - 1U;
						end_reached = false;
						break;
					}
					else
					{
						args.push_back(s_arg);
					}
				}
				if (!(it->second.function(args)))
				{
					args.clear();
					break;
				}
				args.clear();
				if (end_reached)
				{
					break;
				}
			}
		}
		else
		{
			ClearModules();
			RenderHelp(args);
			break;
		}
	}
	for (pair<string, LuaModule *> module : modules)
	{
		module.second->Execute();
	}
	for (pair<string, LuaModule *> module : modules)
	{
		module.second->InvokeEvent("init");
	}
	while (modules.size() > 0)
	{
		vector<string> disabled_modules;
		map<string, LuaModule *>::iterator it;
		for (pair<string, LuaModule *> module : modules)
		{
			if (module.second->IsActive())
			{
				module.second->InvokeEvent("tick");
				if (!(module.second->IsActive()))
				{
					disabled_modules.push_back(module.first);
				}
			}
			else
			{
				disabled_modules.push_back(module.first);
			}
		}
		for (string module : disabled_modules)
		{
			it = modules.find(module);
			if (it != modules.end())
			{
				modules.erase(it);
			}
		}
		disabled_modules.clear();
		this_thread::sleep_for(milliseconds(5));
	}
	for (pair<string, LuaModule *> module : modules)
	{
		module.second->InvokeEvent("exit");
	}
	ClearModules();
	if (arguments.size() == 0)
	{
		RenderHelp(args);
	}
	return 0;
}

#if defined(MOONLIGHT_CONTROLLER_WINDOWS) && defined(MOONLIGHT_CONTROLLER_NO_CONSOLE_APP)

// Main entry point
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	string file_name(__argv[0]);
	vector<string> args;
	for (int i(1); i < __argc; i++)
	{
		args.push_back(__argv[i]);
	}
	return Main(file_name, args);
}

#else

// Main entry point
int main(int argc, char *argv[])
{
	string file_name(argv[0]);
	vector<string> args;
	for (int i(1); i < argc; i++)
	{
		args.push_back(argv[i]);
	}
	return Main(file_name, args);
}
#endif
