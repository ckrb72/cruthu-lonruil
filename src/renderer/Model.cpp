#include "model.h"
#include <graphics.h>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


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
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(path, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

        if (scene == nullptr)
        {
            std::cout << "Failed to open file: " << path << std::endl;
            return false;
        }


        return true;
    };
}