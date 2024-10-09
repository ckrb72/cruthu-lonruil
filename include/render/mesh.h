#pragma once
#include <vector>
#include <render/vertex.h>
#include <render/texture.h>

namespace cl
{
    class mesh
    {
        private:
            std::vector<vertex> m_vertices;
            std::vector<unsigned int> m_indices;
            // Probably don't want to include textures per mesh

            unsigned int vao, vbo, ebo;

        public:
            mesh() {}

            // NOTE:
            // Copy constructor simply copies gpu buffer handles over
            // DOES NOT create a new buffer on the GPU
            mesh(const mesh& m);
            ~mesh() {}

            //bool generate_mesh(std::vector<vertex>& vertices, std::vector<unsigned int>& indices, std::vector<texture>& textures);
    };
}