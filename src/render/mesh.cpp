#include <render/mesh.h>

namespace cl
{
    mesh::mesh(const mesh& m)
    {
        vao = m.vao;
        ebo = m.ebo;
        vbo = m.vbo;

        m_vertices = m.m_vertices;
        m_indices = m.m_indices;
    }


    bool generate_mesh(std::vector<vertex>& vertices, 
                       std::vector<unsigned int>& indices,
                       std::vector<texture>& textures)
    {

        // OpenGL generation stuff here

        
        return true;
    }
}
