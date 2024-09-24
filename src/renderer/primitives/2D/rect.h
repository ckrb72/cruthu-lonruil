#pragma once
#include "../../../math/clmath.h"
#include "../../texture.h"

namespace cl
{
    class rect
    {
        private:
            unsigned int m_glID, m_texbuf;
            float m_x, m_y, m_z;
            float m_width, m_height;
            glm::vec3 color = { 1.0, 1.0, 1.0 };    /* Default Color: White */

            /* TODO: */
            /* Want to have this be a pointer to a texture in a texture manager */
            /* So we don't need to create the same texture multiple times */
            texture* tex = nullptr;

            void gen_rect();
        public:

            rect();
            rect(float width, float height);
            rect(float x, float y, float z, float width, float height);
            rect(const glm::vec3& pos, const glm::vec2& scale);
            rect(const rect& r);
            ~rect();

            void set_pos(glm::vec3& pos);
            void set_pos(float x, float y, float z);

            void set_scale(float width, float height);
            void set_width(float w);
            void set_height(float h);

            void set_color(glm::vec3& c);
            void set_color(float r, float g, float b);

    };
}