#version 410 core

in vec3 f_color;
in vec2 f_tex_coords;

out vec4 output_color;

uniform sampler2D container;

void main()
{
    output_color = vec4(f_color, 1.0) * texture(container, f_tex_coords);
}