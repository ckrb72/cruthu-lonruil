#include "camera.h"

namespace cl
{
    camera::camera()
    {

    }

    camera::camera(const camera& c)
    {

    }

    camera::~camera()
    {

    }

    void camera::set_pos(const glm::vec3& pos)
    {
        m_pos = pos;
        m_dirty = true;
    }

    void camera::set_pos(float x, float y, float z)
    {
        m_pos.x = x;
        m_pos.y = y;
        m_pos.z = z;

        m_dirty = true;
    }


    void camera::set_direction(const glm::vec3& dir)
    {
        m_dir = dir;

        m_dirty = true;
    }

    void camera::set_direction(float x, float y, float z)
    {
        m_dir.x = x;
        m_dir.y = y;
        m_dir.z = z;

        m_dirty = true;
    }

    void camera::gen_orthographic_projection(float left, float right, float bottom, 
                                             float top, float near, float far)
    {
        m_projection = glm::ortho(left, right, bottom, top, near, far);
        m_dirty = true;
    }

    void camera::gen_perspective_projection(float fovy, float aspect, float near, float far)
    {
        m_projection = glm::perspective(fovy, aspect, near, far);
        m_dirty = true;
    }

    glm::mat4& camera::get_view()
    {
        if(m_dirty)
            gen_matrices();
        
        return m_view;
    }

    glm::mat4& camera::get_projection()
    {
        /* Don't need to regen this if cam is dirty since */
        /* we will always immediately regen this whenever we gen projection */
        return m_projection;
    }

    glm::mat4& camera::get_viewprojection()
    {
        if(m_dirty)
            gen_matrices();

        return m_viewprojection;
    }

    void camera::gen_matrices()
    {
        m_view = glm::lookAt(m_pos, m_dir, m_up);
        m_viewprojection = m_projection * m_view;
        m_dirty = false;
    }

}