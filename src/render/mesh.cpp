#include <render/mesh.h>
#include <graphics.h>
#include <utility>
#include <vector>
#include <render/texture.h>
#include <render/vertex.h>
#include <iostream>

namespace cl
{
    mesh::~mesh()
    {
        release();
    }

    void mesh::release()
    {
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
        glDeleteBuffers(1, &m_vao);
        m_index_count = 0;
    }

    mesh::mesh(const mesh& other)
    :m_vao(other.m_vao), m_vbo(other.m_vbo), m_ebo(other.m_ebo)
    {
        mesh& m = (mesh&)other;
    
        m.m_vao = 0;
        m.m_vbo = 0;
        m.m_ebo = 0;
    }

    mesh::mesh(mesh&& other)
    :m_vao(other.m_vao), m_vbo(other.m_vbo), m_ebo(other.m_ebo)
    {
        other.m_vao = 0;
        other.m_vbo = 0;
        other.m_ebo = 0;
    }

    mesh& mesh::operator=(const mesh& other)
    {
        if(this != &other)
        {
            release();
            m_vao = other.m_vao;
            m_vbo = other.m_vbo;
            m_ebo = other.m_ebo;
            m_index_count = other.m_index_count;

            mesh& m = (mesh&)other;
            m.m_vao = 0;
            m.m_ebo = 0;
            m.m_vbo = 0;
            m.m_index_count = 0;
        }

        return *this;
    }

    mesh& mesh::operator=(mesh&& other)
    {
        if(this != &other)
        {
            release();
            std::swap(m_vao, other.m_vao);
            std::swap(m_vbo, other.m_vbo);
            std::swap(m_ebo, other.m_ebo);
            std::swap(m_index_count, other.m_index_count);
        }

        return *this;
    }

    bool mesh::generate_mesh(std::vector<vertex> vertices,
                             std::vector<unsigned int> indices,
                             std::vector<texture> textures)
    {
        // OpenGL commands here

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, color));
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, tex_coords));
        glEnableVertexAttribArray(3);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        this->m_index_count = indices.size();

        return true;
    }


    void mesh::draw()
    {
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, NULL);
        glBindVertexArray(0);
    }
}