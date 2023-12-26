#version 330 core

out vec4 fragmentColor;

uniform vec3 u_outlineColor;

void main() {
    fragmentColor = vec4(u_outlineColor, 1.0);
}