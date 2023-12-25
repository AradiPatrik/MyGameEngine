#version 330 core

in vec2 v_uv;

out vec4 fragmentColor;

uniform sampler2D u_texture;

void main()
{
    fragmentColor = texture(u_texture, v_uv);
}
