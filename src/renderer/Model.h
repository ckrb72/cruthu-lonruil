#pragma once
#include <string>
#include <vector>
#include "Vertex.h"


namespace cl
{
    class model
    {
    private:
        unsigned int m_vao, m_vbo, m_ebo;

        bool gen_model_gpu();

    public:

        model();
        ~model();

        bool load(const std::string& path);
        bool load(std::vector<vertex>& vertices);
    };
}