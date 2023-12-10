#pragma once

#include <functional>
#include <string>
#include <vector>

namespace MoonlightControllerCLI {

	class Command {
	public:

		Command() = delete;
		
		Command(const std::string& description, const std::string& helpTopic, const std::function<bool(const std::vector<std::string>&)>& onCommandExecuted);

		Command(std::string&& description, std::string&& helpTopic, std::function<bool(const std::vector<std::string>&)>&& onCommandExecuted) noexcept;
		
		Command(const Command& command);
		
		Command(Command&& command) noexcept;

		const std::string& GetDescription() const noexcept;

		std::string& GetDescription(std::string& result) const;
		
		const std::string& GetHelpTopic() const noexcept;
		
		std::string& GetHelpTopic(std::string& result) const;

		bool operator()(const std::vector<std::string>& commandArguments) const noexcept;
		
		Command& operator =(const Command& command);
		
		Command& operator =(Command&& command) noexcept;

	private:

		std::string description;

		std::string helpTopic;

		std::function<bool(const std::vector<std::string>&)> onCommandExecuted;
	};
}
