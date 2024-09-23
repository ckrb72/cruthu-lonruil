#pragma once

namespace cl
{
    class rect
    {
        private:
            unsigned int m_glID, m_texbuf;
            float m_x, m_y;
            float m_width, m_height;

            void gen_rect();
        public:

            rect();
            rect(float width, float height);
            rect(float x, float y, float width, float height);
            rect(const rect& r);
            ~rect();

    };
}