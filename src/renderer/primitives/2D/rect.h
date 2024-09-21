#pragma once

namespace cl
{
    class rect
    {
        private:
            unsigned int m_glID;
            float m_x, m_y;
            float m_width, m_height;

        public:

            rect();
            rect(float width, float height);
            rect(float x, float y, float width, float height);
            rect(const rect& r);
            ~rect();

    };
}