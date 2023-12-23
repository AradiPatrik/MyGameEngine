//
// Created by Patrik Aradi on 2023/12/22.
//

#ifndef MULTIPLELITECUBE_H
#define MULTIPLELITECUBE_H
#include "LightAttenuation.h"

#ifdef WIN32
#include <glad/glad.h>
#else
#include <OpenGL/gl3.h>
#endif
#include <glm/glm.hpp>
#include <vector>
#include "../engine/Shader.h"

namespace Engine {
class Texture;
class Camera;
class Shader;
}
struct PhongLightProperties {
    PhongLightProperties(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular)
        : ambient(ambient)
        , diffuse(diffuse)
        , specular(specular)
    {
    }

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct DirectionalLight {
    DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
        : DirectionalLight(
              direction,
              PhongLightProperties(ambient, diffuse, specular))
    {
    }

    DirectionalLight(glm::vec3 direction, PhongLightProperties phongLightProperties)
        : direction(direction)
        , phongLightProperties(phongLightProperties)
    {
    }

    glm::vec3 direction;
    PhongLightProperties phongLightProperties;
};

struct PointLight {
    PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, LightAttenuation::AttenuationRadius atennuationRadius = LightAttenuation::A_50)
        : PointLight(
              position,
              PhongLightProperties(ambient, diffuse, specular),
              atennuationRadius)
    {
    }

    PointLight(glm::vec3 position, PhongLightProperties phongLightProperties, LightAttenuation::AttenuationRadius atennuationRadius = LightAttenuation::A_50)
        : position(position)
        , phongLightProperties(phongLightProperties)
        , attenuationRadius(atennuationRadius)
    {
    }

    glm::vec3 position;
    PhongLightProperties phongLightProperties;
    LightAttenuation::AttenuationRadius attenuationRadius;
};

struct SpotLight {
    SpotLight(glm::vec3 position,
        glm::vec3 direction,
        float innerConeCutoffAngle,
        float outerConeCutoffAngle,
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular,
        LightAttenuation::AttenuationRadius atennuationRadius = LightAttenuation::A_50)
        : SpotLight(
              position,
              direction,
              innerConeCutoffAngle,
              outerConeCutoffAngle,
              PhongLightProperties(ambient, diffuse, specular),
              atennuationRadius)
    {
    }

    SpotLight(
        glm::vec3 position,
        glm::vec3 direction,
        float innerConeCutoffAngle,
        float outerConeCutoffAngle,
        PhongLightProperties phongLightProperties,
        LightAttenuation::AttenuationRadius atennuationRadius = LightAttenuation::A_50)
        : position(position)
        , direction(direction)
        , innerConeCutoffAngle(innerConeCutoffAngle)
        , outerConeCutoffAngle(outerConeCutoffAngle)
        , phongLightProperties(phongLightProperties)
        , attenuationRadius(atennuationRadius)
    {
    }

    glm::vec3 position;
    glm::vec3 direction;

    float innerConeCutoffAngle;
    float outerConeCutoffAngle;

    PhongLightProperties phongLightProperties;
    LightAttenuation::AttenuationRadius attenuationRadius;
};

class MultipleLiteCube {
public:
    MultipleLiteCube(const DirectionalLight& directionalLight, const std::vector<PointLight>& pointLights, const std::vector<SpotLight>& spotLights, const Engine::Camera& camera, const Engine::Texture& diffuseMap, const Engine::Texture& specularMap);

    void setPosition(const glm::vec3&);
    void setRotation(const glm::vec3&);
    void update(float deltaTime);
    void draw() const;

private:
    GLuint m_vao = 0;

    glm::vec3 m_position{};
    glm::vec3 m_rotation{};

    const DirectionalLight& m_directionalLight;
    const std::vector<PointLight>& m_pointLights;
    const std::vector<SpotLight>& m_spotLights;

    Engine::Shader m_shader;
    const Engine::Camera& m_camera;
    const Engine::Texture& m_diffuseMap;
    const Engine::Texture& m_specularMap;
};

#endif // MULTIPLELITECUBE_H
