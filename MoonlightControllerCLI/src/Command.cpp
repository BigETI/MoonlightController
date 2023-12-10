#include <functional>
#include <string>
#include <utility>
#include <vector>

#include <Command.hpp>

using namespace MoonlightControllerCLI;
using namespace std;

Command::Command(const string& description, const string& helpTopic, const function<bool(const vector<string>&)>& onCommandExecuted) :
	description(description),
	helpTopic(helpTopic),
	onCommandExecuted(onCommandExecuted) {
	// ...
}

Command::Command(string&& description, string&& helpTopic, function<bool(const vector<string>&)>&& onCommandExecuted) noexcept :
	description(description),
	helpTopic(helpTopic),
	onCommandExecuted(onCommandExecuted) {
	// ...
}

Command::Command(const Command& command) : description(command.description), helpTopic(command.helpTopic), onCommandExecuted(command.onCommandExecuted) {
	// ...
}

Command::Command(Command&& command) noexcept :
	description(std::move(command.description)),
	helpTopic(std::move(command.helpTopic)),
	onCommandExecuted(std::move(command.onCommandExecuted)) {
	// ...
}

const string& Command::GetDescription() const noexcept {
	return description;
}

string& Command::GetDescription(string& result) const {
	return result = description;
}

const string& Command::GetHelpTopic() const noexcept {
	return helpTopic;
}

string& Command::GetHelpTopic(string& result) const {
	return result = helpTopic;
}

bool Command::operator()(const std::vector<std::string>& commandArguments) const noexcept {
	return onCommandExecuted(commandArguments);
}
Command& Command::operator =(const Command& command) {
	description = command.description;
	helpTopic = command.helpTopic;
	onCommandExecuted = command.onCommandExecuted;
	return *this;
}

Command& Command::operator =(Command&& command) noexcept {
	description = std::move(command.description);
	helpTopic = std::move(command.helpTopic);
	onCommandExecuted = std::move(command.onCommandExecuted);
	return *this;
}
