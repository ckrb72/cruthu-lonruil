#version 410 core
layout(location = 0) out vec4 pos_tex;
layout(location = 1) out vec4 norm_tex;
layout(location = 2) out vec4 spec_tex; // also doubles as albedo (x, y, z = color; a = spec)

uniform sampler2D diffuse;
uniform sampler2D specular;

in vec2 f_tex;
in vec3 f_norm;
in vec3 frag_pos;

void main()
{
    pos_tex = vec4(frag_pos, 1.0);
    norm_tex = vec4(normalize(f_norm), 1.0);
    spec_tex.rgb = texture(diffuse, f_tex).rgb;
    spec_tex.a = 1.0;   // This messes everything up for some reason (should be texture(specular, f_tex).r;)
}