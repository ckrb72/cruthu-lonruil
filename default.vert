#version 410 core

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec2 v_tex_coords;
layout(location = 3) in vec3 v_normal;

out vec3 f_color;
out vec2 f_tex_coords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(v_pos, 1.0);

    f_color = v_color;
    f_tex_coords = v_tex_coords;
}