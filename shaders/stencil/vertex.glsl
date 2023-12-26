#version 330 core

layout (location = 0) in vec3 a_vertexPosition;
layout (location = 1) in vec3 a_vertexNormal;
layout (location = 2) in vec4 a_vertexUv;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform float u_outline;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(a_vertexPosition + (normalize(a_vertexNormal) * u_outline), 1.0);
}
