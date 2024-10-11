#include <render/model.h>
#include <render/mesh.h>
#include <render/texture.h>
#include <render/vertex.h>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

static bool process_node(cl::model* model, aiNode* node, const aiScene* scene);
static std::shared_ptr<cl::mesh> process_mesh(aiMesh* mesh, const aiScene* scene);

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
        std::shared_ptr<cl::mesh> m = process_mesh(node_mesh, scene);

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

static std::shared_ptr<cl::mesh> process_mesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<cl::vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<cl::texture> textures;

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
    }

    std::shared_ptr<cl::mesh> m = std::make_shared<cl::mesh>();
    if(!m->generate_mesh(vertices, indices, textures))
        return nullptr;

    return m;

}