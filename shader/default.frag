#version 410 core

in vec3 f_color;

out vec4 output_color;

void main()
{
    output_color = vec4(f_color, 1.0);
}