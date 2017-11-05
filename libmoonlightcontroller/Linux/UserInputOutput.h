#ifndef __MOONLIGHT_CONTROLLER_USER_INPUT_H__
#   define __MOONLIGHT_CONTROLLER_USER_INPUT_H__

#   include <libmoonlightcontroller/Linux/EUserInputOutputType.h>
#   include <string>
#   include <libevdev/libevdev.h>
#   include <libevdev/libevdev-uinput.h>

// Moonlight controller namespace
namespace MoonlightController
{
    // User input class
    class UserInputOutput
    {
    private:

        // Device
        libevdev *device;

        // User input device
        libevdev_uinput *userInputDevice;
        
        // Default constructor
        UserInputOutput();

        // Copy constructor
        UserInputOutput(const UserInputOutput &);

        // Assign operator
        UserInputOutput & operator = (const UserInputOutput &);

    public:

        // Constructor
        UserInputOutput(EUserInputOutputType userInputOutputType, std::string name);

        // Destructor
        ~UserInputOutput();

        // Write data
        void write(int type, int code, int val);
    };
}
#endif
