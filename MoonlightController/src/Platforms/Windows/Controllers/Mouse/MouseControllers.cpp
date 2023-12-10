#include <cstddef>
#include <memory>
#include <vector>

#include <Controllers/Mouse/IMouseController.hpp>
#include <Controllers/Mouse/MouseControllers.hpp>
#include <Platforms/Windows/Controllers/Mouse/MouseController.hpp>

using namespace MoonlightController::Controllers::Mouse;
using namespace MoonlightController::Platforms::Windows::Controllers::Mouse;
using namespace std;

MouseControllers::MouseControllers() {
	controllers.push_back(make_shared<MouseController>());
}

size_t MouseControllers::GetMaximalControllerCount() noexcept {
	return static_cast<size_t>(1);
}

const vector<shared_ptr<IMouseController>>& MouseControllers::GetControllers() const noexcept {
	return controllers;
}

bool MouseControllers::IsControllerAvailable(size_t controllerIndex) const noexcept {
	return controllerIndex < controllers.size();
}

const IMouseController& MouseControllers::operator [](size_t controllerIndex) const {
	return *controllers.at(controllerIndex);
}
