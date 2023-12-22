#version 330 core
#define MAX_POINT_LIGHTS 10

layout (location = 0) in vec3 a_vertexPosition;
layout (location = 1) in vec3 a_vertexNormal;
layout (location = 2) in vec2 a_vertexUv;

out vec3 v_normal;
out vec3 v_fragmentPosition;
out vec3 v_lightPosition;
out vec2 v_uv;
out vec3 v_directionalLightDirection;
out vec3 v_spotFacing;
out vec3 v_spotPosition;
out vec3 v_pointLightPositions[MAX_POINT_LIGHTS];

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform vec3 u_pointLightPositions[MAX_POINT_LIGHTS];

uniform vec3 u_lightPosition;

uniform vec3 u_directionalLightDirection;

uniform vec3 u_spotFacing;
uniform vec3 u_spotPosition;
uniform int u_pointLightCount;


void main() {
    gl_Position = u_projection * u_view * u_model * vec4(a_vertexPosition, 1.0);
    // TODO: Calculate normal matrix and set it as a uniform
    v_normal = mat3(transpose(inverse(u_view * u_model))) * a_vertexNormal;
    v_fragmentPosition = vec3(u_view * u_model * vec4(a_vertexPosition, 1.0));
    v_lightPosition = vec3(u_view * vec4(u_lightPosition, 1.0));
    v_directionalLightDirection = vec3(u_view * vec4(u_directionalLightDirection, 0.0));
    v_spotFacing = vec3(u_view * vec4(u_spotFacing, 0.0));
    v_spotPosition = vec3(u_view * vec4(u_spotPosition, 1.0));
    for (int i = 0; i < u_pointLightCount; i++) {
        v_pointLightPositions[i] = vec3(u_view * vec4(u_pointLightPositions[i], 1.0));
    }

    v_uv = a_vertexUv;
}
