#include "window/clwindow.h"
#include "event/event.h"
#include <graphics.h>
#include <iostream>
#include <clmath.h>
#include <obj/camera.h>
#include <input/inputManager.h>
#include <cltime.h>
#include <physics/physicsEngine.h>
#include <physics/aabb.h>
#include <render/model.h>

#include <render/vertex.h>
#include <render/2D.h>

#include <render/shader.h>
#include <render/texture.h>

const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;

bool disable_cursor = true;

int main()
{
    cl::window win(WIN_WIDTH, WIN_HEIGHT, "Cruthu Lonruil");
    if(!win.is_open())
    {
        std::cout << "Failed to open window" << std::endl;
        return -1;
    }

     win.disable_cursor(disable_cursor);

    update_delta();

    cl::shader shader;
    if(!shader.load("../shader/container.vert", "../shader/container.frag"))
    {
        std::cerr << "Failed to load shader" << std::endl;
        return -1;
    }

    cl::shader model_shader;
    if(!model_shader.load("../shader/model.vert", "../shader/model.frag"))
    {
        std::cerr << "Failed to load model shader" << std::endl;
        return -1;
    }

    cl::shader aabb_shader;
    if(!aabb_shader.load("../shader/aabb.vert", "../shader/aabb.frag"))
    {
        std::cerr << "Failed to load ababb shader" << std::endl;
        return -1;
    }

    cl::texture tex;
    if(!tex.load("../assets/silly.png", CL_TEXTURE_GENERAL))
    {
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }

    cl::model backpack;
    if(!backpack.load("../assets/backpack/backpack.obj"))
    {
        std::cout << "Failed to load backpack" << std::endl;
        return -1;
    }

    cl::camera cam;
    cam.gen_perspective_projection(glm::radians(59.0f), (float)win.get_width() / win.get_height(), 0.1, 100.0);
    
    cl::inputManager input(win.get_handle());
    //cl::inputManager input;
    //input.init(win.get_handle();

    glLineWidth(3);


    cl::vertex vertices[] = 
    {
        { { -0.5, -0.5, 1.0 }, { 0.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 0.0 } },
        { { 0.5, -0.5, 1.0 }, { 0.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 1.0, 0.0 } },
        { { 0.5, 0.5, 1.0 }, { 0.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 1.0, 1.0 } },
        { { -0.5, 0.5, 1.0 } , { 0.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0 } }
    };

    cl::aabb bounding_box;
    bounding_box.min.x = vertices[0].position.x;
    bounding_box.min.y = vertices[0].position.y;
    bounding_box.min.z = vertices[0].position.z;

    bounding_box.max.x = vertices[0].position.x;
    bounding_box.max.y = vertices[0].position.y;
    bounding_box.max.z = vertices[0].position.z;


    for(int i = 0; i < 4; i++)
    {
        if(vertices[i].position.x < bounding_box.min.x)
            bounding_box.min.x = vertices[i].position.x;

        if(vertices[i].position.y < bounding_box.min.y)
            bounding_box.min.y = vertices[i].position.y;

        if(vertices[i].position.z < bounding_box.min.z)
            bounding_box.min.z = vertices[i].position.z;

        if(vertices[i].position.x > bounding_box.max.x)
            bounding_box.max.x = vertices[i].position.x;

        if(vertices[i].position.y > bounding_box.max.y)
            bounding_box.max.y = vertices[i].position.y;

        if(vertices[i].position.z > bounding_box.max.z)
            bounding_box.max.z = vertices[i].position.z;
    }

    float xspan = bounding_box.max.x - bounding_box.min.x;
    float yspan = bounding_box.max.y - bounding_box.min.y;
    float zspan = bounding_box.max.z - bounding_box.min.z;

    float aabb_vertices[] = 
    {
        bounding_box.min.x, bounding_box.min.y, bounding_box.min.z,
        bounding_box.min.x + xspan, bounding_box.min.y, bounding_box.min.z,
        bounding_box.min.x, bounding_box.min.y, bounding_box.min.z + zspan,
        bounding_box.min.x + xspan, bounding_box.min.y, bounding_box.min.z + zspan,

        bounding_box.min.x, bounding_box.min.y + yspan, bounding_box.min.z,
        bounding_box.min.x + xspan, bounding_box.min.y + yspan, bounding_box.min.z,
        bounding_box.min.x, bounding_box.min.y + yspan, bounding_box.min.z + zspan, 
        bounding_box.min.x + xspan, bounding_box.min.y + yspan, bounding_box.min.z + zspan
    };

    unsigned int aabb_indices[] = 
    {
        2, 3,
        3, 7,
        7, 6,
        6, 2,
        2, 0,
        3, 1,
        6, 4,
        7, 5,
        4, 5,
        5, 1,
        1, 0,
        0, 4
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };


    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    unsigned int color_attachment;
    glGenTextures(1, &color_attachment);
    glBindTexture(GL_TEXTURE_2D, color_attachment);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIN_WIDTH, WIN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attachment, 0);

    unsigned int depth_stencil_buffer;
    glGenRenderbuffers(1, &depth_stencil_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_stencil_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIN_WIDTH, WIN_HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth_stencil_buffer);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Failed to complete framebuffer" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

    glm::vec3 cam_pos = { 0.0, 0.0, 1.0 };
    cam.set_pos(cam_pos);

    shader.set_mat4fv("view", glm::value_ptr(cam.get_view()));

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

    float pitch = 0.0f;
    float yaw = -90.0f;

    /* Render pass has one shader and a buffer that holds all of the data to draw in that pass */

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

        if(disable_cursor)
        {
            yaw += input.get_mouse_dx() * 0.1;
            pitch -= input.get_mouse_dy() * 0.1;
            if(pitch > 89.0f)
                pitch = 89.0f;

            if(pitch < -89.0f)
                pitch = -89.0f;
        }

        /* Calculate camera direction from pitch and yaw */
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction = glm::normalize(direction);

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

        if(input.get_keystate(CLKEY_ESCAPE) == CL_PRESSED)
        {
            disable_cursor = !disable_cursor;
            win.disable_cursor(disable_cursor);
        }
        
        cam.set_pos(cam_pos);
        cam.set_forward(cam_pos + direction);

        /* win.clear() */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

        aabb_shader.bind();
        aabb_shader.set_mat4fv("model", glm::value_ptr(model));
        aabb_shader.set_mat4fv("view", glm::value_ptr(cam.get_view()));

        //glBindVertexArray(aavao);
        //glDrawElements(GL_LINES, sizeof(aabb_indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);


        model_shader.bind();
        model_shader.set_mat4fv("model", glm::value_ptr(model));
        model_shader.set_mat4fv("view", glm::value_ptr(cam.get_view()));
        model_shader.set_mat4fv("projection", glm::value_ptr(cam.get_projection()));
        backpack.draw();

        shader.bind();
        shader.set_mat4fv("model", glm::value_ptr(model));
        shader.set_mat4fv("view", glm::value_ptr(cam.get_view()));

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

        win.swap_buffers();
    }
}