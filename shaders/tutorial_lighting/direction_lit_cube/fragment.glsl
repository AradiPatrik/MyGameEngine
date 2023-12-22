#version 330 core
out vec4 fragmentColor;

in vec3 v_normal;
in vec3 v_fragmentPosition;
in vec3 v_lightPosition;
in vec2 v_uv;
in vec3 v_lightDirection;
in vec3 v_spotFacing;
in vec3 v_spotPosition;

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

uniform float u_constant;
uniform float u_linear;
uniform float u_quadratic;

uniform float u_spotCutOff;
uniform float u_spotInnerConeCosCutoff;
uniform float u_spotOuterConeCosCutoff;

void main()
{
    vec3 pointAmbient = u_light.ambient * vec3(texture(u_material.diffuse, v_uv));

    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(v_lightPosition - v_fragmentPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 pointDiffuse = diff * u_light.diffuse * vec3(texture(u_material.diffuse, v_uv));

    vec3 directionalLightDir = normalize(-v_lightDirection);
    float directionalDiff = max(dot(norm, directionalLightDir), 0.0);
    vec3 directionalDiffuse = directionalDiff * u_directionalLight.light.diffuse * vec3(texture(u_material.diffuse, v_uv));

    vec3 viewDir = normalize(-v_fragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 pointSpecular = spec * u_light.specular * vec3(texture(u_material.specular, v_uv));

    vec3 directionalReflectDir = reflect(-directionalLightDir, norm);
    float directionalSpec = pow(max(dot(viewDir, directionalReflectDir), 0.0), u_material.shininess);
    vec3 directionalSpecular = directionalSpec * u_directionalLight.light.specular * vec3(texture(u_material.specular, v_uv));

    float distance = length(v_lightPosition - v_fragmentPosition);
    float attenuation = 1.0 / (u_constant + u_linear * distance + u_quadratic * (distance * distance));

    pointAmbient *= attenuation;
    pointDiffuse *= attenuation;
    pointSpecular *= attenuation;

    vec3 spotDirection = normalize(v_spotPosition - v_fragmentPosition);

    float cosPhi = dot(spotDirection, normalize(-v_spotFacing));
    vec3 spotDiffuse = vec3(texture(u_material.diffuse, v_uv)) * u_light.diffuse * dot(norm, spotDirection);
    float spotIntensity = 0.0;

    if (cosPhi > u_spotInnerConeCosCutoff) {
        spotIntensity = 1.0;
    } else if (cosPhi > u_spotOuterConeCosCutoff) {
        float theta = cosPhi;
        float epsilon = u_spotInnerConeCosCutoff - u_spotOuterConeCosCutoff;
        spotIntensity = clamp((theta - u_spotOuterConeCosCutoff) / epsilon, 0.0, 1.0);
    }

    float spotDistance = length(v_spotPosition - v_fragmentPosition);
    float spotAttenuation = 1.0 / (u_constant + u_linear * distance + u_quadratic * (spotDistance * spotDistance));
    spotDiffuse *= spotIntensity;

    vec3 spotReflectDir = reflect(-spotDirection, norm);
    vec3 spotSpecular = vec3(texture(u_material.specular, v_uv)) * u_light.specular * pow(max(dot(viewDir, spotReflectDir), 0.0), u_material.shininess);
    spotSpecular *= spotIntensity;

    vec3 result = spotDiffuse + spotSpecular + pointAmbient + pointDiffuse + pointSpecular + directionalDiffuse + directionalSpecular;
    fragmentColor = vec4(result, 1.0);
}
