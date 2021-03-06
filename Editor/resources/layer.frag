#version 330 core
uniform float time;
uniform vec2 resolution;

in vec2 uv;
out vec4 FragColor;

void main()
{
    FragColor = vec4(sin(time)*0.5+0.5, 1.0, cos(uv.y*50.0), 1.0);
}