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
    }

    void camera::set_pos(float x, float y, float z)
    {
        m_pos.x = x;
        m_pos.y = y;
        m_pos.z = z;
    }

    

}