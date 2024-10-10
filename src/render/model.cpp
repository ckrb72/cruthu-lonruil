#include <render/model.h>
#include <render/vertex.h>
#include <render/texture.h>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


static void process_node(cl::model* model, aiNode* node, const aiScene* scene);
static cl::mesh process_mesh(aiMesh* mesh, const aiScene* scene);


namespace cl
{
    
    model::model(const model& m)
    {
        m_meshes = m.m_meshes;
    }

    bool model::load(const std::string& path)
    {
        // FIXME:
        // BAD... DON'T CREATE A NEW IMPORTER EACH TIME WE LOAD A MODEL
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(path, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_FlipUVs);
        if(!scene)
        {
            std::cout << "Failed to load: " << path << std::endl;
            return false;
        }

        process_node(this, scene->mRootNode, scene);

        return true;
    }


    void model::add_mesh(mesh m)
    {
        m_meshes.push_back(m);
    }

}

static void process_node(cl::model* model, aiNode* node, const aiScene* scene)
{
    for(int i = 0; i < node->mNumMeshes; i++)
    {
        // node->mMeshes[i] is an index into scene->mMeshes
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        model->add_mesh(process_mesh(mesh, scene));
    }

    for(int i = 0; i < node->mNumChildren; i++)
    {
        process_node(model, node->mChildren[i], scene);
    }
}

static cl::mesh process_mesh(aiMesh* mesh, const aiScene* scene)
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

        /*
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        */
        
        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.tex_coords = vec;
        }
        else
        {
            vertex.tex_coords = glm::vec2(0.0f, 0.0f);
        }
        
        // TODO:
        // Get colors as well

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

    /*if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<cl::texture> diffuse = load_material_textures(...)
    }*/
    
    cl::mesh m;
    m.generate_mesh(vertices, indices, textures);

    // Note:
    // This copies the mesh which isn't the best solution but works for now
    return m;
}