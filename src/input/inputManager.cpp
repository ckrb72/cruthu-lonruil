#include "inputManager.h"
#include <GLFW/glfw3.h>
#include <iostream>
namespace cl
{

    // Need to figure out how to let this access input manager keyboard
    static void update_keyboard(GLFWwindow* win, int key, int scancode, int action, int mods)
    {
        std::cout << scancode << std::endl;
    }

    inputManager::inputManager()
    {

    }

    inputManager::inputManager(void* win_handle)
    {
        glfwSetKeyCallback((GLFWwindow*)win_handle, update_keyboard);
    }

    inputManager::inputManager(const inputManager& in)
    {

    }

    inputManager::~inputManager()
    {

    }

    keystate inputManager::get_keystate(scancode s)
    {
        return keyboard[s];
    }

    /*void inputManager::update_key(int scancode)
    {

    }*/
}