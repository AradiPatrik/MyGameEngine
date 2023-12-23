//
// Created by Patrik Aradi on 2023/12/6.
//

#ifndef LIGHTCUBE_H
#define LIGHTCUBE_H

#include "../../engine/Shader.h"
#include "MultipleLiteCube.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class LightCube {
public:
    explicit LightCube(PhongLightProperties phongLightProperties);
    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const;
    void setPosition(const glm::vec3& newPosition);
    [[nodiscard]] const glm::vec3& getPosition() const;
    [[nodiscard]] const PhongLightProperties& getLightProperties() const;
    void bindToShader(const Engine::Shader& shader) const;
    void bindToShader(const Engine::Shader&, int index) const;

private:
    GLuint m_vao;

    Engine::Shader m_shader;
    glm::vec3 m_position;

    PhongLightProperties m_phongLightProperties;
};

#endif // LIGHTCUBE_H
