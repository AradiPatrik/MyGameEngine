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

vec3 calculateDirectionalLight(DirectionalLight light, Material material, vec3 normal, vec3 viewDirection)
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_uv));

    vec3 lightDirection = light.direction;
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, v_uv));

    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, v_uv));

    return (ambient + diffuse + specular);
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos) {
    vec3 ambient = light.ambient * vec3(texture(u_material.diffuse, v_uv));

    vec3 lightDirection = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_material.diffuse, v_uv));

    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(normalize(-v_fragmentPosition), reflectDirection), 0.0), u_material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(u_material.specular, v_uv));

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
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

    result += calculateDirectionalLight(directionalLight, u_material, normalize(v_normal), normalize(-v_fragmentPosition));

    fragmentColor = vec4(result, 1.0);
}
