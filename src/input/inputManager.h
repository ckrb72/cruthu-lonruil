#pragma once
#include <cstdint>

#define CL_NUM_SCANCODES 348    // Number of scancodes glfw supports

#define CL_MBLEFT 0 
#define CL_MBRIGHT 1
#define CL_MBMIDDLE 2

enum keystate
{
    CLKEY_UNPRESSED,
    CLKEY_PRESSED,
    CLKEY_HELD
};

enum scancode
{
    PUT,
    SCANCODES,
    HERE
};

enum mouseButtonState
{
    CLMB_UP,
    CLMB_DOWN
};

struct mouseState
{
    int32_t x, y;
    int32_t dx, dy;

    mouseButtonState buttons[3];
};



namespace cl
{
    class inputManager
    {
        private:
            mouseState mouse;
            keystate keyboard[CL_NUM_SCANCODES];

        public:
            inputManager();
            inputManager(void* win_handle);
            inputManager(const inputManager& in);
            ~inputManager();

            keystate get_keystate(scancode s);
    };
}