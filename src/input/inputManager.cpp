#include "inputManager.h"
#include <GLFW/glfw3.h>
#include <iostream>
namespace cl
{
    inputManager::inputManager(void* win_handle)
    {
        m_win_handle = win_handle;
    }

    inputManager::inputManager(const inputManager& in)
    {
        for(int i = 0; i < CL_NUMKEYCODES; i++)
        {
            keyboard[i] = in.keyboard[i];
        }
    }

    keystate inputManager::get_keystate(keycode s)
    {
        return keyboard[s];
    }

    void inputManager::update_key(int keycode)
    {
        int state = glfwGetKey((GLFWwindow*)m_win_handle, keycode);

        if(state == GLFW_PRESS)
        {
            if(keyboard[keycode] == CL_RELEASED)
            {
                /* If first frame down, set CL_PRESSED */
                keyboard[keycode] = CL_PRESSED;
            }
            else
            {

                /* If key already pressed, set CL_HELD */
                keyboard[keycode] = CL_HELD;
            }
        }
        else
        {
            keyboard[keycode] = CL_RELEASED;
        }
    }

    void inputManager::update()
    {
        /* Go through all the keycodes, updating state as needed */
        for(int key = CLKEY_SPACE; key < CL_NUMKEYCODES; key++)
        {
            update_key(key);
        }
    }
}