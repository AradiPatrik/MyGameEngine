#version 330 core
out vec4 fragmentColor;

in vec3 v_normal;
in vec3 v_fragmentPosition;

uniform vec3 u_objectColor;
uniform vec3 u_lightColor;
uniform vec3 u_lightPosition;
uniform vec3 u_viewPosition;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_lightColor;

    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(u_lightPosition - v_fragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_viewPosition - v_fragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);

    float specular = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 result = (ambient + diffuse + specular) * u_objectColor;
    fragmentColor = vec4(result, 1.0);
}
