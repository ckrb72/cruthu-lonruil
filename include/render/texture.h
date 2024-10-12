#pragma once
#include <string>

enum TexType
{
    CL_TEXTURE_GENERAL,
    CL_TEXTURE_DIFFUSE,
    CL_TEXTURE_SPECULAR
};

namespace cl
{

    // REDO: Want to turn this into a struct and cut down on the complexity
    // Should be a thing wrapper around OpenGL Textures
    class texture
    {
    private:
        unsigned int m_id;
        unsigned int m_width, m_height, m_channels;

        std::string m_path;
        TexType m_type;

        bool gpu_gen_texture(const unsigned char* image);
        bool load_texture(const std::string& path);

        void release();

    public:
        texture() {}
        ~texture();

        // Copy constructors as recommended by Khronos Wiki
        texture(const texture& other);
        texture& operator=(const texture& other);
        texture(texture&& other);
        texture& operator=(texture&& other);

        bool load(const std::string& path);
        bool load(const std::string& path, TexType type);

        inline unsigned int get_width() const { return m_width; }
        inline unsigned int get_height() const { return m_height; }
        inline unsigned int get_channels() const { return m_channels; }
        inline unsigned int get_id() const { return m_id; }
        inline TexType get_type() const { return m_type; }
        inline std::string path() const { return m_path; }
    };
}