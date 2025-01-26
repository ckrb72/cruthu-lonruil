#version 410 core
layout(location = 0) out vec4 pos_tex;
layout(location = 1) out vec4 norm_tex;
layout(location = 2) out vec4 albedo_tex; // also doubles as albedo (x, y, z = color; a = spec)
layout(location = 3) out vec4 spec_tex;

uniform sampler2D diffuse;
uniform sampler2D specular;

in vec2 f_tex;
in vec3 f_norm;
in vec3 frag_pos;

void main()
{
    pos_tex = vec4(frag_pos, 1.0);
    norm_tex = vec4(normalize(f_norm), 1.0);
    albedo_tex = texture(diffuse, f_tex);
    spec_tex = texture(specular, f_tex);
}