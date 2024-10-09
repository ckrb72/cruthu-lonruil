#pragma once
#include "../clmath.h"

/* TODO: come up with good way to implement both a forward and direction vector */
/*       problem comes up because they both depend on each other but are used both */
/*       the same or differently depending on the context */

namespace cl
{
    class camera
    {
        private:

            /* Orientation */
            glm::vec3 m_pos = glm::vec3(1.0, 0.0, 1.0);
            glm::vec3 m_forward = glm::vec3(0.0, 0.0, 0.0);
            glm::vec3 m_up = glm::vec3(0.0, 1.0, 0.0);

            /* Matrices */
            glm::mat4 m_view = glm::mat4(1.0);
            glm::mat4 m_projection = glm::mat4(1.0);
            //glm::mat4 m_viewprojection = glm::mat4(1.0);

            float m_sens = 1.0f;
            bool m_dirty = true;

            void gen_matrices();

        public:
            camera();
            camera(const camera& c);
            ~camera();


            void set_pos(const glm::vec3& pos);
            void set_pos(float x, float y, float z);
            //void set_dir(const glm::vec3& dir);
            void set_forward(const glm::vec3& forward);
            //void set_dir(float x, float y, float z);
            void gen_orthographic_projection(float left, float right, float bottom, 
                                             float top, float near, float far);
            void gen_perspective_projection(float fovy, float aspect, float near, float far);
            inline glm::vec3 get_pos() { return m_pos; }
            inline glm::vec3 get_dir() { return glm::normalize(m_forward - m_pos); }
            inline glm::vec3 get_up()  { return m_up; }

            glm::mat4& get_view();
            glm::mat4& get_projection();
            //glm::mat4& get_viewprojection();

            void set_sensitivity(float sens);
    };
}