#version 330 core

layout (location = 0) in vec3 a_vertexPosition;
layout (location = 1) in vec3 a_vertexNormal;

out vec3 v_normal;
out vec3 v_fragmentPosition;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(a_vertexPosition, 1.0);
    // TODO: Calculate normal matrix and set it as a uniform
    v_normal = mat3(transpose(inverse(u_model))) * a_vertexNormal;
    v_fragmentPosition = vec3(u_model * vec4(a_vertexPosition, 1.0));
}
