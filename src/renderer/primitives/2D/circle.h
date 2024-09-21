#pragma once

namespace cl
{
    class circle
    {
        private:
            unsigned int m_glID;
            float radius;
            float x, y;

        public:

            circle();
            circle(const circle* c);
            circle(float x, float y, float radius);
            ~circle();

            void set_radius(float r);
            float get_radius();

            void set_pos(float x, float y);
            void set_x(float x);
            void set_y(float y);
    };
};