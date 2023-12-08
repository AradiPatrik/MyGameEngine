#version 330 core
out vec4 fragmentColor;

uniform vec3 u_objectColor;
uniform vec3 u_lightColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_lightColor;

    vec3 result = u_lightColor * u_objectColor;
    fragmentColor = vec4(result, 1.0);
}
