#include "rect.h"
#include "../../vertex.h"
#include <graphics.h>

namespace cl
{
    rect::rect()
    {
        m_width = 1.0f;
        m_height = 1.0f;
        m_x = 0.0f;
        m_y = 0.0f;
        gen_rect();
        
    }

    rect::~rect()
    {
        glDeleteBuffers(1, &m_texbuf);
        glDeleteVertexArrays(1, &m_glID);
    }

    void rect::gen_rect()
    {

        float vertices[] = 
        {
            -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0,
            0.5, 0.5, 0.0
            -0.5, 0.5, 0.0
        };

        unsigned int indices[] = 
        {
            0, 1, 2,
            2, 3, 0
        };

        unsigned int vao, vbo, ebo, tex;

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        //glGenBuffers(1, &tex);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        /* TODO: */
        /* Make sure this is correct */
        /*glBindBuffer(GL_ARRAY_BUFFER, tex);
        glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);*/

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


        /* TODO: */
        /* Need to figure out how to pass texture data in separately in a decently efficient way */
        /* Probably set up buffer here and then glBufferSubData when you get the tex coords */

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}