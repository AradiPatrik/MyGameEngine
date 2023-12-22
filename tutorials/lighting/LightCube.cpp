//
// Created by Patrik Aradi on 2023/12/6.
//

#include "LightCube.h"
#include "../../engine/MeshUtils.h"

LightCube::LightCube(PhongLightProperties phongLightProperties)
    : m_vao(MeshUtils::createBoxVao())
    , m_shader("shaders/tutorial_lighting/light_cube/vertex.glsl",
          "shaders/tutorial_lighting/light_cube/fragment.glsl")
    , m_position(0, 0, 0)
    , m_phongLightProperties(std::move(phongLightProperties))
{
}

void LightCube::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = translate(modelMatrix, m_position);
    MeshUtils::drawBox(m_shader, m_vao, modelMatrix, viewMatrix, projectionMatrix);
}

void LightCube::setPosition(const glm::vec3& newPosition)
{
    m_position = newPosition;
}

const glm::vec3& LightCube::getPosition() const
{
    return m_position;
}

const PhongLightProperties& LightCube::getLightProperties() const
{
    return m_phongLightProperties;
}

void LightCube::bindToShader(const Shader& shader) const
{
    shader.setUniform("u_lightPosition", m_position);
    shader.setUniform("u_light.ambient", m_phongLightProperties.ambient);
    shader.setUniform("u_light.diffuse", m_phongLightProperties.diffuse);
    shader.setUniform("u_light.specular", m_phongLightProperties.specular);
    shader.setUniform("u_constant", 1.0f);
    shader.setUniform("u_linear", PointLightAttenuation::linear[A_50]);
    shader.setUniform("u_quadratic", PointLightAttenuation::quadratic[A_50]);
}
