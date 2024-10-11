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
            std::string path;


        public:
            model() {}
            model(const model& m) = delete;
            ~model() {}


            bool load(const std::string& path);
            void add_mesh(std::shared_ptr<mesh> m);

            void draw();
    };
}