#include <cstddef>
#include <memory>
#include <vector>

#include <Windows.h>
#include <Xinput.h>

#include <Controllers/Keyboard/IKeyboardController.hpp>
#include <Controllers/Keyboard/KeyboardControllers.hpp>
#include <Platforms/Windows/Controllers/Keyboard/KeyboardController.hpp>

using namespace MoonlightController::Controllers::Keyboard;
using namespace MoonlightController::Platforms::Windows::Controllers::Keyboard;
using namespace std;

KeyboardControllers::KeyboardControllers() {
	controllers.push_back(make_shared<KeyboardController>());
}

size_t KeyboardControllers::GetMaximalControllerCount() noexcept {
	return static_cast<size_t>(1);
}

const vector<shared_ptr<IKeyboardController>>& KeyboardControllers::GetControllers() const noexcept {
	return controllers;
}

bool KeyboardControllers::IsControllerAvailable(size_t controllerIndex) const noexcept {
	return controllerIndex < controllers.size();
}

const IKeyboardController& KeyboardControllers::operator [](size_t controllerIndex) const {
	return *controllers.at(controllerIndex);
}
