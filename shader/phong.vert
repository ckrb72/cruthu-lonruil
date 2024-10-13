#version 410 core
layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_norm;
layout(location = 2) in vec3 v_color;
layout(location = 3) in vec2 v_tex;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 f_tex;
out vec3 f_norm;
out vec3 frag_pos;

void main()
{
    gl_Position = projection * view * model * vec4(v_pos, 1.0);
    f_norm = mat3(transpose(inverse(model))) * v_norm;  // Very inefficient... fix this
    f_tex = v_tex;
    frag_pos = vec3(model * vec4(v_pos, 1.0));
}