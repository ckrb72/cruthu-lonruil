#include "window/clwindow.h"
#include "event/event.h"
#include <graphics.h>
#include <iostream>
#include <clmath.h>
#include <obj/camera.h>
#include <input/inputManager.h>
#include <cltime.h>
#include <physics/physicsEngine.h>

#include <render/vertex.h>
#include <render/2D.h>

#include <render/shader.h>
#include <render/texture.h>

const int WIN_WIDTH = 1500;
const int WIN_HEIGHT = 844;

int main()
{
    cl::window win(WIN_WIDTH, WIN_HEIGHT, "Cruthu Lonruil");
    if(!win.is_open())
    {
        std::cout << "Failed to open window" << std::endl;
        return -1;
    }

    update_delta();

    cl::shader shader;
    if(!shader.load("../shader/container.vert", "../shader/container.frag"))
    {
        std::cerr << "Failed to load shader" << std::endl;
        return -1;
    }

    cl::shader aabb_shader;
    if(!aabb_shader.load("../shader/aabb.vert", "../shader/aabb.frag"))
    {
        std::cerr << "Failed to load ababb shader" << std::endl;
        return -1;
    }

    cl::texture tex;
    if(!tex.load("../assets/container.jpg", CL_TEXTURE_GENERAL))
    {
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }

    cl::camera cam;
    cam.gen_perspective_projection(glm::radians(59.0f), (float)win.get_width() / win.get_height(), 0.1, 100.0);
    
    
    cl::inputManager input(win.get_handle());


    glLineWidth(3);


    cl::vertex vertices[] = 
    {
        { { -0.5, -0.5, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 0.0 } },
        { { 0.5, -0.5, 0.0 }, { 0.0, 1.0, 0.0 }, { 1.0, 0.0 } },
        { { 0.5, 0.5, 0.0 }, { 0.0, 0.0, 1.0 }, { 1.0, 1.0 } },
        { { -0.5, 0.5, 0.0 } , { 1.0, 1.0, 1.0 }, { 0.0, 1.0 } }
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

    shader.set_mat4fv("projection", glm::value_ptr(cam.get_projection()));
    shader.set_mat4fv("view", glm::value_ptr(cam.get_view()));

    glm::vec3 cam_pos = { 0.0, 0.0, 1.0 };
    cam.set_pos(cam_pos);

    shader.set_mat4fv("view", glm::value_ptr(cam.get_view()));


    float aabb_vertices[] = 
    {
        -0.5, -0.5, 0.2,
        0.5, -0.5, 0.2,
        0.5, 0.5, 0.2,
        -0.5, 0.5, 0.2,


        -0.5, -0.5, -0.2,
        0.5, -0.5, -0.2,
        0.5, 0.5, -0.2,
        -0.5, 0.5, -0.2
    };

    unsigned int aabb_indices[] = 
    {
        0, 1, 2,
        2, 3, 0,

        4, 0, 3,
        3, 7, 4,

        3, 2, 6,
        6, 7, 3,

        0, 1, 5, 
        5, 4, 0,

        5, 4, 7, 
        7, 6, 5,
        
        1, 5, 6, 
        6, 2, 1
    };

    unsigned int aavao, aavbo, aaebo;
    glGenVertexArrays(1, &aavao);
    glGenBuffers(1, &aavbo);
    glGenBuffers(1, &aaebo);

    glBindVertexArray(aavao);

    glBindBuffer(GL_ARRAY_BUFFER, aavbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aabb_vertices), aabb_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, aaebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(aabb_indices), aabb_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    aabb_shader.set_mat4fv("projection", glm::value_ptr(cam.get_projection()));

    float move_speed = 1.5f;

    while(!win.should_close())
    {
        update_delta();

        clPollEvents();

        glm::mat4 model(1.0);

        input.update();

        if(input.get_mousebutton(CLMB_LEFT) == CL_PRESSED)
        {
            std::cout << "Left MB Pressed" << std::endl;
            std::cout << input.get_mouse_x() << " " << input.get_mouse_y() << std::endl;
        }

        glm::vec3 dir = cam.get_dir();
        glm::vec3 up = cam.get_up();

        if(input.get_keystate(CLKEY_D))
            cam_pos += glm::cross(dir, up) * move_speed * (float)delta;
        
        if(input.get_keystate(CLKEY_A))
            cam_pos -= glm::cross(dir, up) * move_speed * (float)delta;

        if(input.get_keystate(CLKEY_W))
            cam_pos += dir * move_speed * (float)delta;
        
        if(input.get_keystate(CLKEY_S))
            cam_pos -= dir * move_speed * (float)delta;

        if(input.get_keystate(CLKEY_SPACE))
            cam_pos.y += move_speed * delta;
        
        if(input.get_keystate(CLKEY_LSHIFT))
            cam_pos.y -= move_speed * delta;
        
        cam.set_pos(cam_pos);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

        shader.bind();
        shader.set_mat4fv("model", glm::value_ptr(model));
        shader.set_mat4fv("view", glm::value_ptr(cam.get_view()));

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

        aabb_shader.bind();
        aabb_shader.set_mat4fv("model", glm::value_ptr(model));
        aabb_shader.set_mat4fv("view", glm::value_ptr(cam.get_view()));

        glBindVertexArray(aavao);
        glDrawElements(GL_LINE_STRIP, sizeof(aabb_indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

        win.swap_buffers();
    }
}