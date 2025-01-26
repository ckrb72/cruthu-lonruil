#version 410 core

uniform sampler2D pos_tex;
uniform sampler2D norm_tex;
uniform sampler2D albedo_tex;
uniform sampler2D spec_tex;

uniform vec3 light_pos;
uniform vec3 view_pos;

in vec2 f_tex;

out vec4 final_color;

void main()
{   
    vec3 frag_color = texture(albedo_tex, f_tex).rgb;
    vec3 frag_pos = texture(pos_tex, f_tex).rgb;

    vec3 ambient = frag_color * 0.1;

    vec3 norm = normalize(texture(norm_tex, f_tex).rgb); 
    vec3 light_dir = normalize(light_pos - frag_pos);
    vec3 diffuse = max(dot(norm, light_dir), 0.0) * frag_color;

    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 halfway_dir = normalize(view_dir + light_dir);
    vec3 specular = pow(max(dot(halfway_dir, norm), 0.0), 16.0) * texture(spec_tex, f_tex).rgb;

    final_color = vec4(ambient + diffuse + specular, 1.0);
}