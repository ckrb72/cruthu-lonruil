#pragma once
#include "../types.h"

#define CL_RELEASED 0
#define CL_PRESSED 1
#define CL_HELD 2
#define CL_DRAG 2             /* Same as CL_HELD but we usually talk about mice being dragged, not held */

#define CL_NUMKEYCODES 348    // Number of scancodes glfw supports
#define CL_NUMMB 3

enum mousebutton
{
    CLMB_LEFT,
    CLMB_RIGHT,
    CLMB_MIDDLE
};

enum keycode
{
    CLKEY_SPACE = 32,
    CLKEY_APOSTROPHE = 39,
    CLKEY_COMMA = 44,
    CLKEY_MINUS = 45,
    CLKEY_PERIOD = 46,
    CLKEY_SLASH = 47,
    CLKEY_0 = 48,
    CLKEY_1 = 49,
    CLKEY_2 = 50,
    CLKEY_3 = 51,
    CLKEY_4 = 52,
    CLKEY_5 = 53,
    CLKEY_6 = 54,
    CLKEY_7 = 55,
    CLKEY_8 = 56,
    CLKEY_9 = 57,
    CLKEY_SEMICOLON = 59,
    CLKEY_EQUAL = 61,
    CLKEY_A = 65,
    CLKEY_B = 66,
    CLKEY_C = 67,
    CLKEY_D = 68,
    CLKEY_E = 69,
    CLKEY_F = 70,
    CLKEY_G = 71,
    CLKEY_H = 72,
    CLKEY_I = 73,
    CLKEY_J = 74,
    CLKEY_K = 75,
    CLKEY_L = 76,
    CLKEY_M = 77,
    CLKEY_N = 78,
    CLKEY_O = 79,
    CLKEY_P = 80,
    CLKEY_Q = 81,
    CLKEY_R = 82,
    CLKEY_S = 83,
    CLKEY_T = 84,
    CLKEY_U = 85,
    CLKEY_V = 86,
    CLKEY_W = 87,
    CLKEY_X = 88,
    CLKEY_Y = 89,
    CLKEY_Z = 90,
    CLKEY_LEFT_BRACKET = 91,
    CLKEY_BACKSLASH = 92,
    CLKEY_RIGHT_BRACKET = 93,
    CLKEY_GRAVE_ACCENT = 96,
    CLKEY_WORLD_1 = 161,
    CLKEY_WORLD_2 = 162,
    CLKEY_ESCAPE = 256,
    CLKEY_ENTER = 257,
    CLKEY_TAB = 258,
    CLKEY_BACKSPACE = 259,
    CLKEY_INSERT = 260,
    CLKEY_DELETE = 261,
    CLKEY_RIGHT = 262,
    CLKEY_LEFT = 263,
    CLKEY_DOWN = 264,
    CLKEY_UP = 265,
    CLKEY_PAGE_UP = 266,
    CLKEY_PAGE_DOWN = 267,
    CLKEY_HOME = 268,
    CLKEY_END = 269,
    CLKEY_CAPS_LOCK = 280,
    CLKEY_SCROLL_LOCK = 281,
    CLKEY_NUM_LOCK = 282,
    CLKEY_PRINT_SCREEN = 283,
    CLKEY_PAUSE = 284,
    CLKEY_F1 = 290,
    CLKEY_F2 = 291,
    CLKEY_F3 = 292,
    CLKEY_F4 = 293,
    CLKEY_F5 = 294,
    CLKEY_F6 = 295,
    CLKEY_F7 = 296,
    CLKEY_F8 = 297,
    CLKEY_F9 = 298,
    CLKEY_F10 = 299,
    CLKEY_F11 = 300,
    CLKEY_F12 = 301,
    CLKEY_F13 = 302,
    CLKEY_F14 = 303,
    CLKEY_F15 = 304,
    CLKEY_F16 = 305,
    CLKEY_F17 = 306,
    CLKEY_F18 = 307,
    CLKEY_F19 = 308,
    CLKEY_F20 = 309,
    CLKEY_F21 = 310,
    CLKEY_F22 = 311, 
    CLKEY_F23 = 312,
    CLKEY_F24 = 313,
    CLKEY_F25 = 314,
    CLKEY_KP_0 = 320,
    CLKEY_KP_1 = 321,
    CLKEY_KP_2 = 322,
    CLKEY_KP_3 = 323,
    CLKEY_KP_4 = 324,
    CLKEY_KP_5 = 325,
    CLKEY_KP_6 = 326,
    CLKEY_KP_7 = 327,
    CLKEY_KP_8 = 328,
    CLKEY_KP_9 = 329,
    CLKEY_KP_DECIMAL = 330,
    CLKEY_KP_DIVIDE = 331,
    CLKEY_KP_MULTIPLY = 332,
    CLKEY_KP_SUBTRACT = 333,
    CLKEY_KP_ADD = 334,
    CLKEY_KP_ENTER = 335,
    CLKEY_KP_EQUAL = 336,
    CLKEY_LEFT_SHIFT = 340,
    CLKEY_LEFT_CONTROL = 341,
    CLKEY_LEFT_ALT = 342,
    CLKEY_LEFT_SUPER = 343,
    CLKEY_RIGHT_SHIFT = 344,
    CLKEY_RIGHT_CONTROL = 345,
    CLKEY_RIGHT_ALT = 346,
    CLKEY_RIGHT_SUPER = 347,
    CLKEY_MENU = 348,
};


struct mouseState
{
    double x, y;
    int32 dx, dy;

    int buttons[3];
};



namespace cl
{
    class inputManager
    {
        private:
            void* m_win_handle = nullptr;
            mouseState mouse;
            int keyboard[CL_NUMKEYCODES];

            //controller controllers[MAX_CONTROLLERS];

            void update_key(int keycode);
            void update_mouse();

        public:
            inputManager(void* win_handle);
            inputManager(const inputManager& in);
            ~inputManager() {}

            void update();
            int get_keystate(keycode s) const;
            int get_mousebutton(mousebutton m) const;
            int get_mouse_x() const;
            int get_mouse_y() const;
            void get_mouse_pos(double& x, double& y);
            int get_mouse_dx() const;
            int get_mouse_dy() const;
    };
}