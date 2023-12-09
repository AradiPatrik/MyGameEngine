#version 330 core

layout (location = 0) in vec3 a_vertexPosition;
layout (location = 1) in vec3 a_vertexNormal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform vec3 u_lightPosition;

uniform vec3 u_objectColor;
uniform vec3 u_lightColor;

out vec3 v_vertexColor;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(a_vertexPosition, 1.0);
    vec3 vertexNormal = normalize(mat3(transpose(inverse(u_view * u_model))) * a_vertexNormal);
    vec3 vertexPosition = vec3(u_view * u_model * vec4(a_vertexPosition, 1.0));
    vec3 lightPosition = vec3(u_view * vec4(u_lightPosition, 1.0));

    float ambientStrength = 0.1;
    vec3 ambient = u_lightColor * ambientStrength;

    vec3 lightDirection = normalize(lightPosition - vertexPosition);
    float diffuseStrength = max(dot(lightDirection, vertexNormal), 0);
    vec3 diffuse = diffuseStrength * u_lightColor;

    vec3 reflectedLightDir = normalize(reflect(lightDirection, vertexNormal));
    float specularStrength = pow(max(dot(reflectedLightDir, normalize(vertexPosition)), 0.0), 32);
    vec3 specular = specularStrength * u_lightColor;

    v_vertexColor = (ambient + diffuse + specular) * u_objectColor;
}
