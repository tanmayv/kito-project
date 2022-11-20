#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    float y = 1 - TexCoords.y;
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, vec2(TexCoords.x, y)).r);
    color = vec4(textColor, 1.0) * sampled;
}  