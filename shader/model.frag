#version 410 core

out vec4 final_color;

in vec3 f_norm;

void main()
{
    final_color = vec4(f_norm, 1.0);
}