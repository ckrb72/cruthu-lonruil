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

    int inputManager::get_keystate(keycode s) const
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

        /* Update Mouse */
        update_mouse();
    }

    void inputManager::update_mouse()
    {
        for(int i = CLMB_LEFT; i < 4; i++)
        {
            int state = glfwGetMouseButton((GLFWwindow*)m_win_handle, i);
            
            if(state == GLFW_PRESS)
            {
                if(mouse.buttons[i] == CL_RELEASED)
                {
                    mouse.buttons[i] = CL_PRESSED;
                }
                else
                {
                    mouse.buttons[i] = CL_HELD;
                }
            }
            else
            {
                mouse.buttons[i] = CL_RELEASED;
            }
        }

        /* Update x, y */
        double xpos, ypos;
        glfwGetCursorPos((GLFWwindow*)m_win_handle, &xpos, &ypos);

        /* Update dx, dy */
        mouse.dx = xpos - mouse.x;
        mouse.dy = ypos - mouse.y;

        mouse.x = xpos;
        mouse.y = ypos;
    }

    int inputManager::get_mousebutton(mousebutton m) const
    {
        return mouse.buttons[m];
    }

    double inputManager::get_mouse_x() const
    {
        return mouse.x;
    }
    double inputManager::get_mouse_y() const
    {
        return mouse.y;
    }

    double inputManager::get_mouse_dx() const
    {
        return mouse.dx;
    }
    double inputManager::get_mouse_dy() const
    {
        return mouse.dy;
    }
}