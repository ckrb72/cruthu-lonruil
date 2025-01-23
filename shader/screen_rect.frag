#version 410 core

uniform sampler2D frame_tex;

in vec2 f_tex;

out vec4 final_color;

void main()
{
    final_color = texture(frame_tex, f_tex);
}