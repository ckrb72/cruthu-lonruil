#include <render/model.h>
#include <render/mesh.h>
#include <render/texture.h>
#include <render/vertex.h>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

static bool process_node(cl::model* model, aiNode* node, const aiScene* scene);
static std::shared_ptr<cl::mesh> process_mesh(cl::model* model, aiMesh* mesh, const aiScene* scene);
static bool load_textures(cl::model* model, aiMaterial* material, aiTextureType type, TexType tex_type, std::vector<std::shared_ptr<cl::texture>>& textures);

namespace cl
{
    bool model::load(const std::string& path)
    {
        Assimp::Importer importer;
        
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

        if(!scene)
        {
            std::cout << "Failed to load scene" << std::endl;
            return false;
        }

        directory = path.substr(0, path.find_last_of('/'));

        process_node(this, scene->mRootNode, scene);
        return true;
    }

    void model::add_mesh(std::shared_ptr<mesh> m)
    {
        m_meshes.push_back(m);
    }

    void model::draw()
    {
        for(int i = 0; i < m_meshes.size(); i++)
        {
            m_meshes[i]->draw();
        }
    }
}


static bool process_node(cl::model* model, aiNode* node, const aiScene* scene)
{
    for(int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* node_mesh = scene->mMeshes[node->mMeshes[i]];
        std::shared_ptr<cl::mesh> m = process_mesh(model, node_mesh, scene);

        if(m == nullptr)
        {
            std::cout << "Failed to load mesh" << std::endl;
            return false;
        }

        model->add_mesh(m);
    }

    for(int i = 0; i < node->mNumChildren; i++)
    {
        process_node(model, node->mChildren[i], scene);
    }

    return true;
}

static std::shared_ptr<cl::mesh> process_mesh(cl::model* model, aiMesh* mesh, const aiScene* scene)
{
    std::vector<cl::vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<cl::texture>> textures;

    for(int i = 0; i < mesh->mNumVertices; i++)
    {
        cl::vertex vertex;

        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;

        vertex.position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;

        vertex.normal = vector;

        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.tex_coords = vec;
        }
        else
        {
            vertex.tex_coords = glm::vec2(0.0, 0.0);
        }

        vertices.push_back(vertex);
    }

    for(int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    if(mesh->mMaterialIndex >= 0)
    {
        // Process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        if(!load_textures(model, material, aiTextureType_DIFFUSE, CL_TEXTURE_DIFFUSE, textures))
            return nullptr;
    }

    std::shared_ptr<cl::mesh> m = std::make_shared<cl::mesh>();
    if(!m->generate_mesh(vertices, indices, textures))
        return nullptr;

    return m;

}


static bool load_textures(cl::model* model, aiMaterial* material, aiTextureType type, TexType tex_type, std::vector<std::shared_ptr<cl::texture>>& textures)
{
    for(int i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString str;
        material->GetTexture(type, i, &str);
        
        // Get full path of texture we want to load
        std::string full_path = model->get_directory() + "/" + str.C_Str();

        // Get all loaded textures
        std::vector<std::shared_ptr<cl::texture>>& loaded_textures = model->get_textures();

        bool found = false;
        for(int j = 0; j < loaded_textures.size(); j++)
        {
            // Compare path of texture we want to load with path of loaded textures
            if(std::strcmp(loaded_textures[j]->path().c_str(), full_path.c_str()) == 0)
            {
                // If found, push back the already loaded texture
                textures.push_back(loaded_textures[i]);
                found = true;
                break;
            }
        }

        // If we found the texture already, don't load it again so continue
        if(found)
            continue;

        
        std::shared_ptr<cl::texture> tex = std::make_shared<cl::texture>();

        if(!tex->load(full_path, tex_type))
        {
            std::cout << "FAILED TEXTURE: " << full_path  << std::endl;
            return false;
        }

        textures.push_back(tex);
        loaded_textures.push_back(tex);
    }

    return true;
}