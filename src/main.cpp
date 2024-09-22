#include "window/clwindow.h"
#include "event/event.h"
#include <string.h>
#include <graphics.h>
#include "util/clfile.h"
#include <iostream>
#include "math/clmath.h"
#include "obj/camera.h"
#include "input/inputManager.h"


#include "renderer/vertex.h"
#include "renderer/primitives/2D.h"

#include "renderer/shader.h"
#include "renderer/texture.h"

const int WIN_WIDTH = 1500;
const int WIN_HEIGHT = 844;

int main()
{

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(WIN_WIDTH) / (float)WIN_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat q;


    cl::window win(WIN_WIDTH, WIN_HEIGHT, "Cruthu Lonruil");
    if(!win.is_open())
    {
        std::cout << "Failed to open window" << std::endl;
        return -1;
    }

    cl::shader shader;
    if(!shader.load("./default.vert", "./default.frag"))
    {
        std::cerr << "Failed to load shader" << std::endl;
    }

    cl::texture tex;
    if(!tex.load("./assets/container.jpg", CL_TEXTURE_GENERAL))
    {
        return -1;
    }

    cl::camera cam;
    cl::inputManager input(win.get_handle());


    cl::vertex vertices[] = 
    {
        { { -0.5, -0.5, -5.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 0.0 } },
        { { 0.5, -0.5, -5.0 }, { 0.0, 1.0, 0.0 }, { 1.0, 0.0 } },
        { { 0.5, 0.5, -5.0 }, { 0.0, 0.0, 1.0 }, { 1.0, 1.0 } },
        { { -0.5, 0.5, -5.0 } , { 1.0, 1.0, 1.0 }, { 0.0, 1.0 } }
    };


    unsigned int indices[] = 
    {
        0, 1, 2, 
        2, 3, 0
    };

    unsigned int vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cl::vertex), (void*)offsetof(cl::vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(cl::vertex), (void*)(offsetof(cl::vertex, color)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(cl::vertex), (void*)(offsetof(cl::vertex, tex_coords)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    shader.bind();
    shader.set_int("container", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex.get_id());

    shader.set_mat4fv("projection", glm::value_ptr(projection));
    shader.set_mat4fv("view", glm::value_ptr(view));

    while(!win.should_close())
    {

        clPollEvents();

        glm::mat4 model(1.0);


        shader.set_mat4fv("model", glm::value_ptr(model));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

        win.swap_buffers();
    }

}

/*

glfw_input_callback(GLFWwindow* window, other, stuff)
{
    update input system stuff in here by passing to our own input system class
    so we can then access it in our own input class
}

*/