#pragma once
#include <stdint.h>
#include <render/texture.h>
#include <render/vertex.h>
#include <memory>

namespace cl
{
    class mesh
    {
        private:

            void release();

        public:

            unsigned int m_vao = 0, m_vbo = 0, m_ebo = 0;
            uint32_t m_index_count = 0;
            std::vector<std::shared_ptr<texture>> m_textures;

            mesh() {}
            ~mesh();
            
            // Copy constructors as recommended by Khronos Wiki
            mesh(const mesh& other);
            mesh& operator=(const mesh& other);
            mesh(mesh&& other);
            mesh &operator=(mesh&& other);

            bool generate_mesh(std::vector<vertex> vertices, 
                                     std::vector<unsigned int> indices,
                                     std::vector<std::shared_ptr<texture>> textures);

            void draw();

    };
}