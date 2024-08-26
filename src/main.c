#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <GLFW/glfw3.h>

void resize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "NameTBD", NULL, NULL);

    if(!window)
        exit(-1);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize_callback);

    #if !defined(__APPLE__)
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("failed to load glad!\n");
        exit(-1);
    }
    #endif


    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0.3, 0.3, 0.3, 1.0);

        glfwSwapBuffers(window);
    }



    glfwDestroyWindow(window);
    glfwTerminate();

    glfwMakeContextCurrent(window);
}