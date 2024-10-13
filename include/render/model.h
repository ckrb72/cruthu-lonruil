#pragma once
#include <vector>
#include <render/mesh.h>
#include <string>
#include <memory>


namespace cl
{
    class model
    {
        private:

            // PERFORMANCE: Using smart ptrs because copy constructors are hard
            // Will fix those if performance becomes an issue
            std::vector<std::shared_ptr<mesh>> m_meshes;
            std::vector<std::shared_ptr<texture>> m_textures;
            std::string directory;


        public:
            model() {}
            model(const model& m) = delete;
            ~model() {}


            bool load(const std::string& path);
            void add_mesh(std::shared_ptr<mesh> m);

            inline std::string& get_directory() { return directory; }
            inline std::vector<std::shared_ptr<texture>>& get_textures() { return m_textures; }

            void draw();
    };
}