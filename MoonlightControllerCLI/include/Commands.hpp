#pragma once

#include <functional>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "Command.hpp"

namespace MoonlightControllerCLI {

	class Commands {
	public:

		Commands();

		Commands(const std::string::value_type& commandPrefix);

		Commands(std::string::value_type&& commandPrefix) noexcept;

		Commands(const Commands& commands);

		Commands(Commands&& commands) noexcept;

		std::string::value_type GetCommandPrefix() const noexcept;

		const std::map<std::string, Command>& GetCommands() const noexcept;

		std::map<std::string, Command>& GetCommands(std::map<std::string, Command>& result) const;

		const std::unordered_map<std::string, std::string>& GetAliases() const noexcept;

		std::unordered_map<std::string, std::string>& GetAliases(std::unordered_map<std::string, std::string>& result) const noexcept;

		const std::unordered_map<std::string, std::vector<std::string>>& GetReverseAliasLookup() const noexcept;

		std::unordered_map<std::string, std::vector<std::string>>& GetReverseAliasLookup(std::unordered_map<std::string, std::vector<std::string>>& result) const noexcept;

		bool AddCommand(
			const std::string& commandName,
			const std::string& description,
			const std::string& helpTopic,
			const std::function<bool(const std::vector<std::string>&)>& onCommandExecuted
		);

		bool AddCommand(
			std::string&& commandName,
			std::string&& description,
			std::string&& helpTopic,
			std::function<bool(const std::vector<std::string>&)>&& onCommandExecuted
		);

		bool AddAlias(const std::string& alias, const std::string& commandName);

		bool AddAlias(std::string&& alias, std::string&& commandName);

		bool ParseCommands(const std::vector<std::string>& arguments);

		Commands& operator =(const Commands& commands);

		Commands& operator =(Commands&& commands) noexcept;

	private:

		std::string::value_type commandPrefix;

		std::map<std::string, Command> commands;

		std::unordered_map<std::string, std::string> aliases;

		std::unordered_map<std::string, std::vector<std::string>> reverseAliasLookup;
	};
}
