#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include "renderer/window.h"
#include "event/events.h"

int main()
{
    window_t* window = clCreateWindow(800, 600, "cruthu lonruil");


    while(!clWindowShouldClose(window))
    {
        clPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0.3, 0.3, 0.3, 1.0);

        clSwapBuffers(window);
    }

    clDestroyWindow(window);

}