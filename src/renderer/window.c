#include "window.h"
#include <stdint.h>
#include <stdbool.h>
#include <graphics.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>



static bool graphics_api_setup(void* handle);
static void* create_window_handle(int width, int height, const char* title);
static void destroy_window_handle(void* window);



typedef struct window_t
{
    void* handle;
    int width;
    int height;
}window_t;



window_t* clCreateWindow(int width, int height, const char* title)
{

    window_t* window = malloc(sizeof(window));

    window->width = width;
    window->height = height;
    window->handle = create_window_handle(width, height, title);

    if(!window->handle)
        return NULL;

    if(!graphics_api_setup(window->handle))
    {
        destroy_window_handle(window->handle);
        return NULL;
    }


    return window;
}




void clDestroyWindow(window_t* window)
{
    if(!window)
        return;

    destroy_window_handle(window->handle);
    free(window);
}



bool clWindowShouldClose(window_t* window)
{
    if(!window)
        return false;
    
    return glfwWindowShouldClose((GLFWwindow*)window->handle);
}

void clSwapBuffers(window_t* window)
{
    glfwSwapBuffers((GLFWwindow*)window->handle);
}



// Initializes graphics api for rendering
static bool graphics_api_setup(void* handle)
{

    if(!handle)
        return false;

    #if !defined(__APPLE__)
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return 0;
    #endif
}


// Creates window handle for window_t struct
// If fails, returns NULL and destroys glfw context (no need to call glfwTerminate() if result is NULL)
static void* create_window_handle(int width, int height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

    if(!window)
    {
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);


    return (void*)window;
}


static void destroy_window_handle(void* window)
{
    if(!window)
        return;

    glfwDestroyWindow((GLFWwindow*)window);
    glfwTerminate();
}