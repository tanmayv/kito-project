#version 330 core
out vec4 FragColor;
uniform mat4 projection;
uniform float test;

void main()
{
    FragColor = vec4(projection[0][0] * 100, 0.0f, 0.0f, 1.0f);
} 