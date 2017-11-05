#include <libmoonlightcontroller/Linux/UserInputOutput.h>

using namespace MoonlightController;
using namespace std;

UserInputOutput::UserInputOutput(EUserInputOutputType userInputOutputType, string name) : device(nullptr), userInputDevice(nullptr)
{
    device = libevdev_new();
    if (device)
    {
        libevdev_set_name(device, name.c_str()); 
        libevdev_enable_event_type(device, EV_KEY);
        for (int i(1); i <= 248; i++)
        {
            libevdev_enable_event_code(device, EV_KEY, i, nullptr);
        }
        if (libevdev_uinput_create_from_device(device, LIBEVDEV_UINPUT_OPEN_MANAGED, &userInputDevice) != 0)
        {
            libevdev_free(device);
            device = nullptr;
            userInputDevice = nullptr;
        }
    }
}

UserInputOutput::~UserInputOutput()
{
    if (userInputDevice)
    {
        libevdev_uinput_destroy(userInputDevice);
        userInputDevice = nullptr;
        device = nullptr;
    }
    if (device)
    {
        libevdev_free(device);
        device = nullptr;
    }
}

void UserInputOutput::write(int type, int code, int val)
{
    if (userInputDevice)
    {
        libevdev_uinput_write_event(userInputDevice, type, code, val);
    }
}
