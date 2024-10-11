#include <render/texture.h>
#include <climage.h>
#include <graphics.h>
#include <iostream>
#include <utility>

namespace cl
{
    void texture::release()
    {

    }

    texture::~texture()
    {
        release();
    }

    texture::texture(const texture& other)
    :m_id(other.m_id), m_width(other.m_width), m_height(other.m_height), 
    m_channels(other.m_channels), m_path(other.m_path), m_type(other.m_type)
    {
        texture& t = (texture&)other;
        t.m_id = 0;
        t.m_width = 0;
        t.m_height = 0;
        t.m_channels = 0;
        t.m_path = "";
        t.m_type = CL_TEXTURE_GENERAL;
    }

    texture::texture(texture&& other)
    :m_id(other.m_id), m_width(other.m_width), m_height(other.m_height), 
    m_channels(other.m_channels), m_path(other.m_path), m_type(other.m_type)
    {
        other.m_id = 0;
        other.m_width = 0;
        other.m_height = 0;
        other.m_channels = 0;
        other.m_path = "";
        other.m_type = CL_TEXTURE_GENERAL;
    }


    texture& texture::operator=(const texture& other)
    {
        if(this != &other)
        {
            release();
            m_id = other.m_id;
            m_width = other.m_width;
            m_height = other.m_height;
            m_channels = other.m_channels;
            m_path = other.m_path;
            m_type = other.m_type;

            // Awful hacky solution but need to make sure other is zero'd out
            texture& t = (texture&)other;
            t.m_id = 0;
            t.m_width = 0;
            t.m_height = 0;
            t.m_channels = 0;
            t.m_path = "";
            t.m_type = CL_TEXTURE_GENERAL;
        }

        return *this;
    }

    texture& texture::operator=(texture&& other)
    {
        if(this != &other)
        {
            release();
            std::swap(m_id, other.m_id);
            std::swap(m_width, other.m_width);
            std::swap(m_height, other.m_height);
            std::swap(m_channels, other.m_channels);
            std::swap(m_path, other.m_path);
            std::swap(m_type, other.m_type);
        }
        return *this;
    }

    bool texture::load(const std::string& path)
    {
        if(!load_texture(path))
            return false;

        m_type = CL_TEXTURE_GENERAL;

        return true;
    }

    bool texture::load(const std::string& path, TexType type)
    {
        if(!load_texture(path))
            return false;

        m_type = type;

        return true;
    }

    bool texture::load_texture(const std::string& path)
    {
        int width, height, channels;

        stbi_set_flip_vertically_on_load(true);

        unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels, 0);

        if(!image)
        {
            std::cout << "failed to load texture: " << path << std::endl; 
            return false;
        }

        m_width = width;
        m_height = height;
        m_channels = channels;


        if(!gpu_gen_texture(image))
        {
            stbi_image_free(image);
            std::cout << "failed to generate texture on GPU: " << path << std::endl;
            return false;
        }

        stbi_image_free(image);

        m_path = path;

        return true;
    }

    bool texture::gpu_gen_texture(const unsigned char* image)
    {
        unsigned int id;

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if(m_channels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        else if(m_channels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        else
            return false;

        glGenerateMipmap(GL_TEXTURE_2D);


        m_id = id;

        return true;
    }
}