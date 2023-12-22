//
// Created by Patrik Aradi on 2023/12/20.
//

#include "DirectionalLitCube.h"
#include "LightCube.h"

void DirectionLitCube::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    m_shader.use();
    m_shader.setUniform("u_lightDirection", lightDirection);
    m_shader.setUniform("u_directionalLight.light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    m_shader.setUniform("u_directionalLight.light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    m_shader.setUniform("u_directionalLight.light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    m_camera.bindSpotLightShader(m_shader);
    LightmapCube::draw(viewMatrix, projectionMatrix);
}

void DirectionLitCube::setLightDirection(const glm::vec3& newLightDirection)
{
    lightDirection = newLightDirection;
}
