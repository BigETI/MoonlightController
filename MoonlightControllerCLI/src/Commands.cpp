#include <functional>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <Commands.hpp>

using namespace MoonlightControllerCLI;
using namespace std;

Commands::Commands() : commandPrefix('-') {
	// ...
}

Commands::Commands(const string::value_type& commandPrefix) : commandPrefix(commandPrefix) {
	// ...
}

Commands::Commands(string::value_type&& commandPrefix) noexcept : commandPrefix(commandPrefix) {
	// ...
}

Commands::Commands(const Commands& commands) : commands(commands.commands), aliases(commands.aliases), reverseAliasLookup(commands.reverseAliasLookup) {
	// ...
}

Commands::Commands(Commands&& commands) noexcept :
	commands(std::move(commands.commands)),
	aliases(std::move(commands.aliases)),
	reverseAliasLookup(std::move(commands.reverseAliasLookup)) {
	// ...
}

string::value_type Commands::GetCommandPrefix() const noexcept {
	return commandPrefix;
}

const map<string, Command>& Commands::GetCommands() const noexcept {
	return commands;
}

map<string, Command>& Commands::GetCommands(map<string, Command>& result) const {
	return result = commands;
}

const unordered_map<string, string>& Commands::GetAliases() const noexcept {
	return aliases;
}

unordered_map<string, string>& Commands::GetAliases(unordered_map<string, string>& result) const noexcept {
	return result = aliases;
}

const unordered_map<string, vector<string>>& Commands::GetReverseAliasLookup() const noexcept {
	return reverseAliasLookup;
}

unordered_map<string, vector<string>>& Commands::GetReverseAliasLookup(unordered_map<string, vector<string>>& result) const noexcept {
	return result = reverseAliasLookup;
}

bool Commands::AddCommand(const string& commandName, const string& description, const string& helpTopic, const function<bool(const vector<string>&)>& onCommandExecuted) {
	bool ret(!commands.contains(commandName) && !aliases.contains(commandName));
	if (ret) {
		commands.insert_or_assign(commandName, Command(description, helpTopic, onCommandExecuted));
	}
	return ret;
}

bool Commands::AddCommand(string&& commandName, string&& description, string&& helpTopic, function<bool(const vector<string>&)>&& onCommandExecuted) {
	bool ret(!commands.contains(commandName) && !aliases.contains(commandName));
	if (ret) {
		commands.insert_or_assign(commandName, Command(description, helpTopic, onCommandExecuted));
	}
	return ret;
}

bool Commands::AddAlias(const string& alias, const string& commandName) {
	bool ret(!commands.contains(alias) && !aliases.contains(alias) && commands.contains(commandName));
	if (ret) {
		aliases.insert_or_assign(alias, commandName);
		auto reverse_alias_lookup_it(reverseAliasLookup.find(commandName));
		if (reverse_alias_lookup_it == reverseAliasLookup.end()) {
			reverseAliasLookup.insert_or_assign(commandName, vector<string>({ alias }));
		}
		else {
			reverse_alias_lookup_it->second.push_back(alias);
		}
	}
	return ret;
}

bool Commands::AddAlias(std::string&& alias, std::string&& commandName) {
	bool ret(!commands.contains(alias) && !aliases.contains(alias) && (commands.contains(commandName) || aliases.contains(commandName)));
	if (ret) {
		aliases.insert_or_assign(alias, commandName);
		auto reverse_alias_lookup_it(reverseAliasLookup.find(commandName));
		if (reverse_alias_lookup_it == reverseAliasLookup.end()) {
			reverseAliasLookup.insert_or_assign(commandName, vector<string>({ alias }));
		}
		else {
			reverse_alias_lookup_it->second.push_back(alias);
		}
	}
	return ret;
}

bool Commands::ParseCommands(const vector<string>& arguments) {
	bool ret(true);
	vector<string> command_arguments;
	for (size_t argument_index(static_cast<size_t>(0)); argument_index != arguments.size(); argument_index++) {
		const string& argument(arguments[argument_index]);
		if (argument[0] == commandPrefix) {
			string argument_without_command_prefix(argument.substr(static_cast<size_t>(1)));
			auto alias_it(aliases.find(argument_without_command_prefix));
			while (alias_it != aliases.end()) {
				argument_without_command_prefix = alias_it->second;
				alias_it = aliases.find(argument_without_command_prefix);
			}
			const auto& command_it(commands.find(argument_without_command_prefix));
			if (command_it == commands.end()) {
				ret = false;
				break;
			}
			else {
				bool is_end_reached(true);
				for (size_t inner_argument_index(argument_index + static_cast<size_t>(1)); inner_argument_index != arguments.size(); inner_argument_index++) {
					const string& inner_argument(arguments[inner_argument_index]);
					if (inner_argument[0] == commandPrefix) {
						argument_index = inner_argument_index - static_cast<size_t>(1);
						is_end_reached = false;
						break;
					}
					else {
						command_arguments.push_back(inner_argument);
					}
				}
				if (!(command_it->second(command_arguments))) {
					command_arguments.clear();
					break;
				}
				command_arguments.clear();
				if (is_end_reached) {
					break;
				}
			}
		}
		else {
			ret = false;
			break;
		}
	}
	return ret;
}

Commands& Commands::operator =(const Commands& commands) {
	this->commands = commands.commands;
	aliases = commands.aliases;
	reverseAliasLookup = commands.reverseAliasLookup;
	return *this;
}

Commands& Commands::operator =(Commands&& commands) noexcept {
	this->commands = std::move(commands.commands);
	aliases = std::move(commands.aliases);
	reverseAliasLookup = std::move(commands.reverseAliasLookup);
	return *this;
}
