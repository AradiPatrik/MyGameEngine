//
// Created by Patrik Aradi on 2023/12/6.
//

#ifndef LIGHTCUBE_H
#define LIGHTCUBE_H

#include "../../engine/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "PhongLightProperties.h"

class PointLightAttenuation {
public:
    static constexpr float linear[] = {
        0.7f,
        0.35f,
        0.22f,
        0.14f,
        0.09f,
        0.07f,
        0.045f,
        0.027f,
        0.022f,
        0.014f,
        0.007f,
        0.0014f,
    };

    static constexpr float quadratic[] = {
        1.8f,
        0.44f,
        0.20f,
        0.07f,
        0.032f,
        0.017f,
        0.0075f,
        0.0028f,
        0.0019f,
        0.0007f,
        0.0002f,
        0.000007f,
    };
};

class LightCube {
public:
    explicit LightCube(PhongLightProperties  phongLightProperties);
    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void setPosition(const glm::vec3& newPosition);
    [[nodiscard]] const glm::vec3& getPosition() const;
    [[nodiscard]] const PhongLightProperties& getLightProperties() const;
    void bindToShader(const Engine::Shader& shader) const;

private:
    GLuint m_vao;

    Engine::Shader m_shader;
    glm::vec3 m_position;

    PhongLightProperties m_phongLightProperties;
    PointLightAttenuation m_attenuation;
};

enum AttenuationRadius {
    A_7 = 0,
    A_13 = 1,
    A_20 = 2,
    A_32 = 3,
    A_50 = 4,
    A_65 = 5,
    A_100 = 6,
    A_160 = 7,
    A_200 = 8,
    A_325 = 9,
    A_600 = 10,
    A_3250 = 11,
};

#endif // LIGHTCUBE_H
