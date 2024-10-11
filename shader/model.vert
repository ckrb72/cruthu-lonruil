#version 410 core
layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_norm;
layout(location = 2) in vec3 v_color;
layout(location = 3) in vec3 v_tex;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 f_norm;

void main()
{
    gl_Position = projection * view * model * vec4(v_pos, 1.0);
    f_norm = v_norm;
}