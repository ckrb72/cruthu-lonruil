#include "time.h"
#include <GLFW/glfw3.h>

static double previous = 0.0f;
double delta = 0.0f;

double get_time()
{
    return glfwGetTime();
}

void update_delta()
{
    double current = glfwGetTime();
    delta = current - previous;
    previous = current;
}