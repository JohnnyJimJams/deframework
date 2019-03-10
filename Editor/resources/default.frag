#version 330 core
uniform float time;
uniform vec2 resolution;

in vec2 uv;
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}