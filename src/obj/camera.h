#pragma once
#include "../math/clmath.h"

namespace cl
{
    class camera
    {
        private:

            /* Orientation */
            glm::vec3 m_pos = { 0.0, 0.0, 0.0 };
            glm::vec3 m_forward = { 0.0, 1.0, 0.0 };
            glm::vec3 m_up = { 0.0, 1.0, 0.0 };

            /* Matrices */
            glm::mat4 m_view = glm::mat4(1.0);
            glm::mat4 m_projection = glm::mat4(1.0);
            glm::mat4 m_viewprojection = glm::mat4(1.0);

            float m_sens = 1.0f;

        public:
            camera();
            camera(const camera& c);
            ~camera();


            void set_pos(const glm::vec3& pos);
            void set_pos(float x, float y, float z);
            inline glm::vec3 get_pos() { return m_pos; }

            inline glm::mat4 get_view() { return m_view; }
            inline glm::mat4 get_projection() { return m_projection; }
            inline glm::mat4 get_viewprojection() { return m_viewprojection; }

            void set_sensitivity(float sens);
    };
}