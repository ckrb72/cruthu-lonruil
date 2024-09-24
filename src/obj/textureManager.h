#pragma once
#include <map>
#include "../renderer/texture.h"

namespace cl
{
    class textureManager
    {
        private:
            std::map<std::string, texture> m_tex;

        public:
            textureManager();
            ~textureManager();

            texture& get_texture(const std::string& name);
            texture& add_texture(const std::string& name, const std::string& path);
    };
}