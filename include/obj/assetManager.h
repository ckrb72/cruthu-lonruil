#pragma once
#include <memory>
#include <render/texture.h>
#include <render/model.h>
#include <map>

namespace cl
{
    class assetManager
    {
        private:


        public:
            assetManager();
            ~assetManager();
            bool init();

            std::shared_ptr<texture> load_texture(std::string& path);
            std::shared_ptr<model> load_model(std::string& path);
            std::shared_ptr<texture> retreive_texture(unsigned int id);
            std::shared_ptr<model> retrieve_model(unsigned int);
    }; 
}