#include "model.h"
#include <graphics.h>
#include <iostream>


namespace cl
{
    model::model()
    {

    };

    model::~model()
    {
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
        glDeleteVertexArrays(1, &m_vao);
    };

    bool load(const std::string& path)
    {
        return true;
    };
}