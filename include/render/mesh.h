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
            std::vector<texture> m_textures;
            // Probably don't want to include textures per mesh

            unsigned int m_vao, m_vbo, m_ebo;

        public:
            mesh() {}

            // NOTE:
            // Copy constructor simply copies gpu buffer handles over
            // DOES NOT create a new buffer on the GPU
            mesh(const mesh& m);
            ~mesh();

            bool generate_mesh(const std::vector<vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<texture>& textures);
    };
}