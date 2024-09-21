#pragma once
#include <string>
#include <map>
#include "../util/clerr.h"


class Shader
{
private:
    unsigned int m_id;

    std::map<std::string, int> m_uniforms;

public: 

    Shader();
    Shader(const Shader& s);
    ~Shader();

    bool load(const std::string& vertex_path, const std::string& fragment_path);

    void bind();
    void unbind();


    void set_int(const std::string& name, int i);
    void set_mat4fv(const std::string& name, float* matrix);
    void set_float(const std::string& name, float f);
    void set_vec3f(const std::string& name, float x, float y, float z);
    void set_vec3fv(const std::string& name, float* vec);




};