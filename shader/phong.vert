#version 410 core
layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_norm;
layout(location = 2) in vec3 v_color;
layout(location = 3) in vec2 v_tex;
layout(location = 4) in vec3 v_tangent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 f_tex;
out vec3 f_norm;
out vec3 frag_pos;
out mat3 TBN;

void main()
{
    gl_Position = projection * view * model * vec4(v_pos, 1.0);
    
    // This is left over from before the normal map
    f_norm = mat3(transpose(inverse(model))) * v_norm;  // Very inefficient... fix this
    
    vec3 T = normalize(vec3(model * vec4(v_tangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(v_norm, 0.0)));
    vec3 B = cross(N, T);
    TBN = mat3(T, B, N);

    f_tex = v_tex;
    frag_pos = vec3(model * vec4(v_pos, 1.0));
}