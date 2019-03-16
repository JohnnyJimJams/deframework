#version 330 core
uniform float time;
uniform vec2 resolution;

in vec2 uv;
in vec3 normal;

out vec4 FragColor;

void main()
{
    float lum = max(dot(normal, normalize(vec3(1.0, 1.0,-1.0))), 0.0);
    FragColor = vec4(0.0, 0.3 + 0.7 * lum, 0.0, 1.0);
}