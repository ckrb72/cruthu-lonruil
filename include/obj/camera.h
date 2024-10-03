#pragma once
#include "../clmath.h"

namespace cl
{
    class camera
    {
        private:

            /* Orientation */
            glm::vec3 m_pos = { 1.0, 0.0, 1.0 };
            glm::vec3 m_dir = { 0.0, 0.0, 0.0 };
            glm::vec3 m_up = { 0.0, 1.0, 0.0 };

            /* Matrices */
            glm::mat4 m_view = glm::mat4(1.0);
            glm::mat4 m_projection = glm::mat4(1.0);
            glm::mat4 m_viewprojection = glm::mat4(1.0);

            float m_sens = 1.0f;
            bool m_dirty = true;

            void gen_matrices();

        public:
            camera();
            camera(const camera& c);
            ~camera();


            void set_pos(const glm::vec3& pos);
            void set_pos(float x, float y, float z);
            void set_direction(const glm::vec3& dir);
            void set_direction(float x, float y, float z);
            void gen_orthographic_projection(float left, float right, float bottom, 
                                             float top, float near, float far);
            void gen_perspective_projection(float fovy, float aspect, float near, float far);
            inline glm::vec3 get_pos() { return m_pos; }

            glm::mat4& get_view();
            glm::mat4& get_projection();
            glm::mat4& get_viewprojection();

            void set_sensitivity(float sens);
    };
}