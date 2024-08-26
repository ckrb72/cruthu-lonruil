#include "events.h"
#include <GLFW/glfw3.h>

void poll_window_events();

void clPollEvents()
{
    poll_window_events();
}



void poll_window_events()
{
    glfwPollEvents();
}