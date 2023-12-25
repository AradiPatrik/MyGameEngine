#version 330 core
#define MAX_POINT_LIGHTS 10

out vec4 fragmentColor;

in vec3 v_normal;
in vec3 v_fragmentPosition;
in vec3 v_lightPosition;
in vec2 v_uv;
in vec3 v_directionalLightDirection;
in vec3 v_spotFacing;
in vec3 v_spotPosition;
in vec3[MAX_POINT_LIGHTS] v_pointLightPositions;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform PointLight u_pointLights[MAX_POINT_LIGHTS];
uniform int u_pointLightCount;

uniform DirectionalLight u_directionalLight;
uniform Material u_material;

vec3 calculateDirectionalLight()
{
    vec3 ambient = u_directionalLight.ambient * vec3(texture(u_material.diffuse, v_uv));

    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(v_directionalLightDirection);
    float directionalDiff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_directionalLight.diffuse * directionalDiff * vec3(texture(u_material.diffuse, v_uv));

    vec3 viewDir = normalize(-v_fragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = u_directionalLight.specular * spec * vec3(texture(u_material.specular, v_uv));

    return ambient + diffuse + specular;
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos) {
    vec3 ambient = light.ambient * vec3(texture(u_material.diffuse, v_uv));

    vec3 lightDirection = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_material.diffuse, v_uv));

    vec3 viewDir = normalize(-v_fragmentPosition);
    vec3 reflectDir = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(u_material.specular, v_uv));

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (diffuse + ambient + specular);
}

void main()
{
    DirectionalLight directionalLight = DirectionalLight(
        normalize(v_directionalLightDirection),
        u_directionalLight.ambient,
        u_directionalLight.diffuse,
        u_directionalLight.specular
    );

    vec3 result = vec3(0.0);

    for (int i = 0; i < u_pointLightCount; i++) {
        PointLight pointLight = PointLight(
            v_pointLightPositions[i],
            u_pointLights[i].constant,
            u_pointLights[i].linear,
            u_pointLights[i].quadratic,
            u_pointLights[i].ambient,
            u_pointLights[i].diffuse,
            u_pointLights[i].specular
        );
        result += calculatePointLight(pointLight, normalize(v_normal), v_fragmentPosition);
        fragmentColor = vec4(result, 1.0);
    }

    result += calculateDirectionalLight();

    fragmentColor = vec4(result, 1.0);
}
