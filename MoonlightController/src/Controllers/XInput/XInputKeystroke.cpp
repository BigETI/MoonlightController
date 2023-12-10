#include <Controllers/XInput/XInputKeystroke.hpp>

using namespace MoonlightController::Controllers::XInput;

XInputKeystroke::XInputKeystroke() :
	virtualKey(static_cast<EXInputVirtualKey>(0)),
	unicode(L'\0'),
	keyboardStates(static_cast<EXInputKeyboardStates>(0)),
	userIndex(0),
	hidCode(0) {
	// ...
}

XInputKeystroke::XInputKeystroke(EXInputVirtualKey virtualKey, wchar_t unicode, EXInputKeyboardStates keyboardStates, int userIndex, unsigned char hidCode) :
	virtualKey(virtualKey),
	unicode(unicode),
	keyboardStates(keyboardStates),
	userIndex(userIndex),
	hidCode(hidCode) {
	// ...
}
