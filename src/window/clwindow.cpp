#include "clwindow.h"
#include <graphics.h>
#include <GLFW/glfw3.h>

#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>

static bool init_graphics_api();

static void window_resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const std::string& title)
:m_title(title)
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if(!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if(!init_graphics_api())
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }

    glfwSetWindowSizeCallback(window, window_resize_callback);

    this->m_width = width;
    this->m_height = height;
    this->m_win_handle = (void*)window;
    this->m_is_open = true;
}

Window::~Window()
{
    glfwDestroyWindow((GLFWwindow*)m_win_handle);
    glfwTerminate();
    m_is_open = false;
}

bool Window::should_close()
{
    return glfwWindowShouldClose((GLFWwindow*)m_win_handle);
}

void Window::swap_buffers()
{
    glfwSwapBuffers((GLFWwindow*)m_win_handle);
}


static bool init_graphics_api()
{
    #if !defined(__APPLE__)
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return false;
    }
    #endif

    glEnable(GL_DEPTH_TEST);

    return true;
}