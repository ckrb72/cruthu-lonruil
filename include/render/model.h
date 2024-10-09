#pragma once
#include <vector>
#include <string>
#include <render/mesh.h>

namespace cl
{
    class model
    {
        private:
            std::vector<mesh> m_meshes;

        public:

            model() {};
            model(const model& m);
            ~model() {};


            bool load(const std::string& path);
            void add_mesh(mesh m);
    };
}