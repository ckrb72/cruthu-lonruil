#pragma once
#include <glm/glm.hpp>


namespace cl
{
    struct vertex
    {
        glm::vec3 position;
        glm::vec3 color;
        //glm::vec3 normal;
        glm::vec2 tex_coords;
    };
}