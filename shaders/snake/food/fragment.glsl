#version 330 core

in vec2 v_uv;

out vec4 fragColor;

uniform vec4 u_color;

void main() {
    fragColor = u_color;
}
