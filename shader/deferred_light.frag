#version 410 core

uniform sampler2D pos_tex;
uniform sampler2D norm_tex;
uniform sampler2D albedo_spec_tex;

uniform vec3 light_pos;
uniform vec3 view_dir;

in vec2 f_tex;

out vec4 final_color;

void main()
{   
    vec3 frag_color = texture(albedo_spec_tex, f_tex).rgb;

    vec3 ambient = frag_color * 0.1;

    vec3 norm = normalize(texture(norm_tex, f_tex).rgb); 
    vec3 light_dir = normalize(light_pos - texture(pos_tex, f_tex).rgb);
    vec3 diffuse = max(dot(norm, light_dir), 0.0) * frag_color;

    final_color = vec4(ambient + diffuse, 1.0);
}