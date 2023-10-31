#version 330 core

in vec4 VertexColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 FragColor;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(-TexCoord.x, TexCoord.y)), 0.2);
}
