#version 330 core
out vec4 fragmentColor;

in vec3 v_normal;
in vec3 v_fragmentPosition;
in vec3 v_lightPosition;

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light u_light;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material u_material;

void main()
{
    vec3 ambient = u_light.ambient * u_material.ambient;

    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(v_lightPosition - v_fragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_light.diffuse * u_material.diffuse;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(-v_fragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess * 128);
    vec3 specular = spec * u_light.specular * u_material.specular;

    vec3 result = ambient + diffuse + specular;
    fragmentColor = vec4(result, 1.0);
}
