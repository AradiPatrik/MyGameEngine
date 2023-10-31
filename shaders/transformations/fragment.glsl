#version 330 core

in vec2 v_texCoord;
out vec4 fragColor;

uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

void main()
{
    fragColor = mix(texture(u_texture1, v_texCoord), texture(u_texture2, v_texCoord), 0.2);
}

