#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

uniform mat4 projectionview;

out vec2 uv;

void main()
{
    uv = aUV;
    gl_Position = projectionview * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}