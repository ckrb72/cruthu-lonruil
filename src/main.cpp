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

    cl::shader model_shader;
    if(!model_shader.load("../shader/model.vert", "../shader/model.frag"))
    {
        std::cerr << "Failed to load model shader" << std::endl;
        return -1;
    }

    cl::shader lighting;
    if(!lighting.load("../shader/phong.vert", "../shader/phong.frag"))
    {
        std::cerr << "Failed to load lighting shader" << std::endl;
        return -1;
    }

    cl::texture tex;
    if(!tex.load("../assets/silly.png", CL_TEXTURE_GENERAL))
    {
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }

    cl::texture backpack_tex;
    if(!backpack_tex.load("../assets/backpack/diffuse.jpg"))
    {
        std::cout << "Failed to load textures" << std::endl;
        return -1;
    }

    cl::model backpack;
    if(!backpack.load("../assets/backpack/backpack.obj"))
    {
        std::cout << "Failed to load backpack" << std::endl;
        return -1;
    }

    cl::model jupiter;
    if(!jupiter.load("../assets/jupiter.obj"))
    {
        std::cout << "Failed to load jupiter" << std::endl;
        return -1;
    }

    cl::model donut;
    if(!donut.load("../assets/donut.fbx"))
    {
        std::cout << "Failed to load donut" << std::endl;
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


    glm::vec3 cam_pos = { 0.0, 0.0, 1.0 };
    cam.set_pos(cam_pos);

    float move_speed = 1.5f;

    float pitch = 0.0f;
    float yaw = -90.0f;
    
    float angle = 0.0f;

    model_shader.set_int("diffuse", 0);

    while(!win.should_close())
    {
        update_delta();

        clPollEvents();

        glm::mat4 model(1.0);

        input.update();

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

        //model_shader.bind();
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, backpack_tex.get_id());

        //model_shader.set_mat4fv("model", glm::value_ptr(model));
        //model_shader.set_mat4fv("view", glm::value_ptr(cam.get_view()));
        //model_shader.set_mat4fv("projection", glm::value_ptr(cam.get_projection()));

        glm::vec3 light_color(1.0);
        glm::vec3 object_color(1.0);
        glm::vec3 light_pos(1.0);
        glm::vec3 cam_pos = cam.get_pos();

        lighting.bind();
        lighting.set_mat4fv("projection", glm::value_ptr(cam.get_projection()));
        lighting.set_mat4fv("view", glm::value_ptr(cam.get_view()));
        lighting.set_mat4fv("model", glm::value_ptr(model));

        // Lighting specific stuff
        lighting.set_vec3fv("light_color", glm::value_ptr(light_color));
        lighting.set_vec3fv("object_color", glm::value_ptr(object_color));
        lighting.set_vec3fv("light_pos", glm::value_ptr(light_pos));
        lighting.set_vec3fv("view_pos", glm::value_ptr(cam_pos));

        backpack.draw();

        /*glm::mat4 jupiter_model = glm::mat4(1.0);
        jupiter_model = glm::translate(jupiter_model, glm::vec3(-2.0, 0.0, 0.0));
        //jupiter_model = glm::scale(jupiter_model, glm::vec3(0.01, 0.01, 0.01));
        jupiter_model = glm::rotate(jupiter_model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        jupiter_model = glm::rotate(jupiter_model, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
        model_shader.set_mat4fv("model", glm::value_ptr(jupiter_model));
        //jupiter.draw();
        donut.draw();*/

        angle += 10.0 * delta;

        win.swap_buffers();
    }
}