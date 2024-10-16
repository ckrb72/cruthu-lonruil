#include <window/clwindow.h>
#include <graphics.h>
#include <GLFW/glfw3.h>
#include <iostream>


namespace cl
{
    static bool init_graphics_api();

    static void window_resize_callback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    window::window(int width, int height, const std::string& title)
    :m_title(title)
    {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_SAMPLES, 4);


        GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if(!window)
        {
            std::cout << "Failed to create window" << std::endl;
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
        glfwSwapInterval(0);

        this->m_width = width;
        this->m_height = height;
        this->m_win_handle = (void*)window;
        this->m_is_open = true;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //glEnable(GL_MULTISAMPLE);

        /*glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW); */
    }

    window::~window()
    {
        glfwDestroyWindow((GLFWwindow*)m_win_handle);
        glfwTerminate();
        m_is_open = false;
    }

    bool window::should_close()
    {
        return glfwWindowShouldClose((GLFWwindow*)m_win_handle);
    }

    void window::swap_buffers()
    {
        glfwSwapBuffers((GLFWwindow*)m_win_handle);
    }

    void window::disable_cursor(bool val)
    {
        if(val)
            glfwSetInputMode((GLFWwindow*)m_win_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
        else
            glfwSetInputMode((GLFWwindow*)m_win_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
}