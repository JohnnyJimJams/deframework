#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 aUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 uv;
out vec3 normal;
out vec2 texcoord;

void main()
{
    uv = aUV;
	normal = normalize(mat3(view) * in_normal);
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}