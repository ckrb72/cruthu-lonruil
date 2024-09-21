#include "texture.h"
#include <climage.h>
#include <graphics.h>
#include <iostream>


namespace cl
{
    texture::texture()
    {

    }

    texture::texture(const texture& t)
    {
        load(t.m_path);
    }

    texture::~texture()
    {
        glDeleteTextures(1, &m_id);
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