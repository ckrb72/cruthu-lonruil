#pragma once
#include <string>

enum TexType
{
    CL_TEXTURE_GENERAL,
    CL_TEXTURE_DIFFUSE,
    CL_TEXTURE_SPECULAR
};

class Texture
{
private:
    unsigned int m_id;
    unsigned int m_width, m_height, m_channels;

    std::string m_path;
    TexType m_type;

    bool gpu_gen_texture(const unsigned char* image);
    bool load_texture(const std::string& path);

public:
    Texture();
    ~Texture();

    bool load(const std::string& path);
    bool load(const std::string& path, TexType type);
    
    inline unsigned int get_width() const { return m_width; }
    inline unsigned int get_height() const { return m_height; }
    inline unsigned int get_channels() const { return m_channels; }
    inline unsigned int get_id() const { return m_id; }
    inline TexType get_type() const { return m_type; }
};