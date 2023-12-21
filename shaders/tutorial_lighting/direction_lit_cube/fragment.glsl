#version 330 core
out vec4 fragmentColor;

in vec3 v_normal;
in vec3 v_fragmentPosition;
in vec3 v_lightPosition;
in vec2 v_uv;
in vec3 v_lightDirection;

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light u_light;

struct DirectionalLight {
    Light light;
};

uniform DirectionalLight u_directionalLight;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material u_material;

void main()
{
    vec3 ambient = u_light.ambient * vec3(texture(u_material.diffuse, v_uv));

    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(v_lightPosition - v_fragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_light.diffuse * vec3(texture(u_material.diffuse, v_uv));

    vec3 directionalLightDir = normalize(-v_lightDirection);
    float directionalDiff = max(dot(norm, directionalLightDir), 0.0);
    vec3 directionalDiffuse = directionalDiff * u_directionalLight.light.diffuse * vec3(texture(u_material.diffuse, v_uv));

    vec3 viewDir = normalize(-v_fragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = spec * u_light.specular * vec3(texture(u_material.specular, v_uv));

    vec3 directionalReflectDir = reflect(-directionalLightDir, norm);
    float directionalSpec = pow(max(dot(viewDir, directionalReflectDir), 0.0), u_material.shininess);
    vec3 directionalSpecular = directionalSpec * u_directionalLight.light.specular * vec3(texture(u_material.specular, v_uv));

    vec3 result = specular + diffuse + ambient + directionalDiffuse + directionalSpecular;
    fragmentColor = vec4(result, 1.0);
}
