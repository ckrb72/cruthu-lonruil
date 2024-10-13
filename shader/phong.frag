#version 410 core

in vec2 f_tex;
in vec3 f_norm;
in vec3 frag_pos;

struct Material
{
    //vec3 ambient;
    //vec3 diffuse;
    sampler2D diffuse;
    //vec3 specular;
    sampler2D specular;
    float shininess;
};

struct Light
{
    //vec3 direction; // For directional lighting
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Light light;
uniform Material material;
uniform vec3 view_pos;

out vec4 final_color;


void main()
{

    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    //float ambient_strength = 0.1;
    //vec3 ambient = ambient_strength * light_color;

    //vec3 ambient = material.ambient * light.ambient;
    vec3 ambient = texture(material.diffuse, f_tex).rgb * light.ambient;

    // Diffuse
    vec3 norm = normalize(f_norm);
    vec3 light_dir = normalize(light.position - frag_pos);
    //vec3 light_dir = normalize(-light.direction); //Used for directional lights
    float diff = max(dot(norm, light_dir), 0.0);    // If dot(norm, light_dir) < 0, make diff 0
    //vec3 diffuse = diff * light_color;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, f_tex).rgb;


    // Specular
    //float specular_strength = 0.5;
    vec3 view_dir = normalize(view_pos - frag_pos);
    //vec3 reflect_dir = reflect(-light_dir, norm);
    //float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    //vec3 specular = specular_strength * spec * light_color;
    vec3 halfway_dir = normalize(light_dir + view_dir);
    //float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    float spec = pow(max(dot(norm, halfway_dir), 0.0), material.shininess);
    //vec3 specular = (spec * material.specular) * light.specular;
    vec3 specular = light.specular * spec * texture(material.specular, f_tex).rgb;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = (ambient + diffuse + specular);

    final_color = vec4(result, 1.0);
}