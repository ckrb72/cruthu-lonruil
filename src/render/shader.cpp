#include <render/shader.h>
#include <util/clfile.h>
#include <iostream>
#include <graphics.h>


#define MAX_LOG 256


namespace cl
{
    shader::shader()
    {

    }

    shader::shader(const shader& s)
    {
        this->m_id = s.m_id;
        this->m_uniforms = s.m_uniforms;
    }


    shader::~shader()
    {
        glDeleteProgram(m_id);
    }

    bool shader::load(const std::string& vertex_path, const std::string& fragment_path)
    {

        int success;
        char log[MAX_LOG];



        std::string vertex_str = clReadFileText(vertex_path);

        const char* const vertex_src = vertex_str.c_str();

        unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_src, nullptr);
        glCompileShader(vertex_shader);



        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertex_shader, MAX_LOG, nullptr, log);
            std::cerr << "Vertex: " << std::endl;
            std::cerr << log << std::endl;
            glDeleteShader(vertex_shader);
            return false;
        }

        std::string fragment_str = clReadFileText(fragment_path);

        const char* const fragment_src = fragment_str.c_str();

        unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_src, nullptr);
        glCompileShader(fragment_shader);

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragment_shader, MAX_LOG, nullptr, log);
            std::cerr << "Fragment: " << std::endl;
            std::cerr << log << std::endl;
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
            return false;
        }

        unsigned int program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(program, MAX_LOG, nullptr, log);

            std::cerr << "Linker: " << std::endl;
            std::cerr << log << std::endl;


            glDetachShader(program, vertex_shader);
            glDetachShader(program, fragment_shader);
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
            glDeleteProgram(program);

            return false;
        }

        glDetachShader(program, vertex_shader);
        glDetachShader(program, fragment_shader);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        m_id = program;

        return true;
    }

    void shader::bind()
    {
        glUseProgram(m_id);
    }

    void shader::unbind()
    {
        glUseProgram(0);
    }

    void shader::set_int(const std::string& name, int i)
    {
        this->bind();
    
        if(m_uniforms.count(name) == 0)
            m_uniforms[name] = glGetUniformLocation(m_id, name.c_str());
    
        glUniform1i(m_uniforms[name], i);
    }
    
    void shader::set_mat4fv(const std::string& name, float* matrix)
    {
        this->bind();
    
        if(m_uniforms.count(name) == 0)
            m_uniforms[name] = glGetUniformLocation(m_id, name.c_str());
    
        glUniformMatrix4fv(m_uniforms[name], 1, GL_FALSE, matrix);
    }
    
    
    
    void shader::set_float(const std::string&name, float f)
    {
        this->bind();
    
        if(m_uniforms.count(name) == 0)
            m_uniforms[name] = glGetUniformLocation(m_id, name.c_str());
    
        glUniform1f(m_uniforms[name], f);
    }
    
    
    
};
