#version 410 core

out vec4 final_color;

in vec3 f_norm;
in vec2 f_tex;

uniform sampler2D diffuse;

void main()
{
    final_color = texture(diffuse, f_tex);
}