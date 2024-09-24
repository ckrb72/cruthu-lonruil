#pragma once
#include "../../../math/clmath.h"

namespace cl
{
    class circle
    {
        private:
            unsigned int m_glID;
            float m_radius;
            float m_x, m_y, m_z;

        public:

            circle();
            circle(const circle* c);
            circle(float x, float y, float z, float radius);
            circle(const glm::vec3& pos, float r);
            ~circle();

            void set_radius(float r);
            float get_radius();

            void set_pos(float x, float y);
            void set_x(float x);
            void set_y(float y);
    };
};