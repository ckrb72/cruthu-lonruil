#pragma once
#include <string>
#include <vector>
#include "Vertex.h"


class Model
{
private:
    unsigned int m_vao, m_vbo, m_ebo;

    bool gen_model_gpu();

public:

    Model();
    ~Model();

    bool load(const std::string& path);
    bool load(std::vector<Vertex>& vertices);

    
};