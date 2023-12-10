#include <chrono>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include <Scripting/Lua/ELuaModuleLibraries.hpp>
#include <Scripting/Lua/LuaModule.hpp>

#include <Command.hpp>
#include <Commands.hpp>

using namespace MoonlightController;
using namespace MoonlightController::Scripting::Lua;
using namespace MoonlightControllerCLI;
using namespace std;
using namespace std::chrono;
using namespace std::filesystem;
using namespace std::this_thread;

static ELuaModuleLibraries luaLibraries(ELuaModuleLibraries::Recommended);

static unordered_map<string, unique_ptr<LuaModule>> luaModules;

static Commands commands;

const static string helpHelpTopic("Show specific help about a command by typing\n\t-h <Command>\n\nExample:\n\t-h m");

static bool RenderHelpCommandExecutedEvent(const vector<string>& arguments) {
	if (!arguments.empty()) {
		string command(arguments[0]);
		auto alias_it(commands.GetAliases().find(command));
		if (alias_it != commands.GetAliases().end()) {
			command = alias_it->second;
			alias_it = commands.GetAliases().find(command);
		}
		const auto& command_it(commands.GetCommands().find(command));
		if (command_it == commands.GetCommands().end()) {
			cerr << "Can not help about command \"" << commands.GetCommandPrefix() << command << "\", because it has not been found." << endl;
		}
		else {
			cout <<
				"\"" <<
				commands.GetCommandPrefix() <<
				command;
			const auto reverse_alias_lookup_it(commands.GetReverseAliasLookup().find(command));
			for (const auto& alias : reverse_alias_lookup_it->second) {
				cout << ", " << commands.GetCommandPrefix() << alias;
			}
			cout << "\": " << command_it->second.GetDescription() << endl << endl << command_it->second.GetHelpTopic() << endl;
		}
	}
	else {
		cout << "Moonlight controller help:" << endl;
		for (const auto& command : commands.GetCommands()) {
			cout << "\t" << commands.GetCommandPrefix() << command.first;
			const auto& reverse_alias_lookup_it(commands.GetReverseAliasLookup().find(command.first));
			if (reverse_alias_lookup_it != commands.GetReverseAliasLookup().end()) {
				for (const auto& alias : reverse_alias_lookup_it->second) {
					cout << ", " << commands.GetCommandPrefix() << alias;
				}
			}
			cout << endl << "\t\t" << command.second.GetDescription() << endl;
		}
		cout << endl << helpHelpTopic << endl;
	}
	cout << endl << "End of help topic" << endl;
	return false;
}

static bool AddModulesCommandExecutedEvent(const vector<string>& arguments) {
	bool ret(false);
	if (!arguments.empty()) {
		ret = true;
		for (const auto& argument : arguments) {
			if (exists(argument)) {
				const auto& lua_module_it(luaModules.find(argument));
				if (lua_module_it == luaModules.end()) {
					try {
						unique_ptr<LuaModule> module(make_unique<LuaModule>(path(argument), luaLibraries));
						if (module->IsActive()) {
							luaModules.emplace(make_pair(argument, std::move(module)));
						}
					}
					catch (exception e) {
						cerr << e.what() << endl;
						break;
					}
					catch (...) {
						cerr << "A fatal error has occured." << endl;
						break;
					}
				}
				else {
					cerr << "Lua module \"" << argument << "\" is already specified." << endl;
				}
			}
			else {
				cerr << "File \"" << argument << "\" does not exist." << endl;
			}
		}
	}
	return ret;
}

int main(int argc, char* argv[]) {
	bool ret(-1);
	string executable_path(argv[0]);
	vector<string> arguments;
	for (int argument_index(1); argument_index < argc; argument_index++) {
		arguments.push_back(argv[argument_index]);
	}
	commands.AddCommand("h", "Shows this help topic", helpHelpTopic, RenderHelpCommandExecutedEvent);
	commands.AddAlias("-help", "h");
	commands.AddCommand("m", "Add Lua modules to load", "Load any Lua modules by typing\n\t-m <Lua modules>\n\nExample:\n\t-m example1.lua example2.lua", AddModulesCommandExecutedEvent);
	commands.AddAlias("-modules", "m");
	if (commands.ParseCommands(arguments)) {
		for (const auto& module : luaModules) {
			module.second->Execute();
		}
		for (const auto& module : luaModules) {
			module.second->InvokeEvent("init");
		}
		vector<string> disabled_modules;
		while (!luaModules.empty()) {
			for (const auto& module : luaModules) {
				if (module.second->IsActive()) {
					module.second->InvokeEvent("tick");
					if (!(module.second->IsActive())) {
						module.second->InvokeEvent("exit");
						disabled_modules.push_back(module.first);
					}
				}
				else {
					module.second->InvokeEvent("exit");
					disabled_modules.push_back(module.first);
				}
			}
			if (!disabled_modules.empty()) {
				for (const auto& disabled_module : disabled_modules) {
					luaModules.erase(disabled_module);
				}
				disabled_modules.clear();
			}
			sleep_for(milliseconds(5));
		}
		if (arguments.empty()) {
			RenderHelpCommandExecutedEvent(arguments);
			ret = 2;
		}
		ret = 0;
	}
	else {
		ret = 1;
	}
	return ret;
}
