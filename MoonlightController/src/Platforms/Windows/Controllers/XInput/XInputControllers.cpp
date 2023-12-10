#include <cstddef>
#include <memory>
#include <vector>

#include <Windows.h>
#include <Xinput.h>

#include <Controllers/XInput/IXInputController.hpp>
#include <Controllers/XInput/XInputControllers.hpp>
#include <Platforms/Windows/Controllers/XInput/XInputController.hpp>

using namespace MoonlightController::Controllers::XInput;
using namespace MoonlightController::Platforms::Windows::Controllers::XInput;
using namespace std;

XInputControllers::XInputControllers() {
	for (size_t index(static_cast<size_t>(0)), maximal_controller_count(GetMaximalControllerCount()); index != maximal_controller_count; index++) {
		controllers.push_back(make_shared<XInputController>(index));
	}
}

size_t XInputControllers::GetMaximalControllerCount() noexcept {
	return static_cast<size_t>(XUSER_MAX_COUNT);
}

const vector<shared_ptr<IXInputController>>& XInputControllers::GetControllers() const noexcept {
	return controllers;
}

bool XInputControllers::IsControllerAvailable(size_t controllerIndex) const noexcept {
	return controllerIndex < controllers.size();
}

const IXInputController& XInputControllers::operator [](size_t controllerIndex) const {
	return *controllers.at(controllerIndex);
}
