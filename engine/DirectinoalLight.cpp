//
// Created by Taipei Home on 12/23/2023.
//

#include "DirectinoalLight.h"

#include "Shader.h"
DirectinoalLight::DirectinoalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
    : m_direction(direction)
    , m_ambient(ambient)
    , m_diffuse(diffuse)
    , m_specular(specular)
{
}

void DirectinoalLight::bindToShader(const Engine::Shader& shader) const
{
    shader.use();
    shader.setUniform("u_directionalLightDirection", m_direction);
    shader.setUniform("u_directionalLight.ambient", m_ambient);
    shader.setUniform("u_directionalLight.diffuse", m_diffuse);
    shader.setUniform("u_directionalLight.specular", m_specular);
}