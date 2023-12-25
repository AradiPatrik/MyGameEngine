//
// Created by Patrik Aradi on 2023/12/22.
//

#include "MultipleLightShaderCube.h"
#include "../../engine/Camera.h"
#include "../../engine/MeshUtils.h"
#include "../../engine/Shader.h"
#include "../../engine/Texture.h"

#include <sstream>

MultipleLightShaderCube::MultipleLightShaderCube(const Texture& diffuseMap, const Texture& specularMap)
    : m_vao(MeshUtils::createBoxWithNormalsAndUvs())
    , m_diffuseMap(diffuseMap)
    , m_specularMap(specularMap)
{
}

void MultipleLightShaderCube::setPosition(const glm::vec3& position)
{
    m_position = position;
}
void MultipleLightShaderCube::setRotation(const glm::vec3& rotation)
{
    m_rotation = rotation;
}
void MultipleLightShaderCube::update(float deltaTime)
{
    // No-op
}
void MultipleLightShaderCube::draw(const Shader& shader) const
{
    glm::mat4 model(1.0f);
    model = translate(model, m_position);
    model = rotate(model, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
    model = rotate(model, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
    model = rotate(model, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));

    shader.use();

    m_diffuseMap.bind(shader, GL_TEXTURE0, "u_material.diffuse");
    m_specularMap.bind(shader, GL_TEXTURE1, "u_material.specular");

    // m_shader.setUniform("u_model", model);
    // m_shader.setUniform("u_view", m_camera.getViewMatrix());
    // m_shader.setUniform("u_projection", m_camera.getProjectionMatrix());
    //
    // m_shader.setUniform("u_material.diffuse", 0);
    // m_shader.setUniform("u_material.specular", 1);
    // m_shader.setUniform("u_material.shininess", 32.0f);
    //
    // m_shader.setUniform("u_directionalLight.ambient", m_directionalLight.phongLightProperties.ambient);
    // m_shader.setUniform("u_directionalLight.diffuse", m_directionalLight.phongLightProperties.diffuse);
    // m_shader.setUniform("u_directionalLight.specular", m_directionalLight.phongLightProperties.specular);
    // m_shader.setUniform("u_directionalLightDirection", m_directionalLight.direction);
    //
    // m_shader.setUniform("u_pointLightCount", static_cast<GLint>(m_pointLights.size()));
    // for (int i = 0; i < m_pointLights.size(); i++) {
    //     std::stringstream ss;
    //     ss << "u_pointLights[" << i << "].";
    //     const auto prefix = ss.str();
    //
    //     const auto& pointLight = m_pointLights[i];
    //     m_shader.setUniform(prefix + "ambient", pointLight.phongLightProperties.ambient);
    //     m_shader.setUniform(prefix + "diffuse", pointLight.phongLightProperties.diffuse);
    //     m_shader.setUniform(prefix + "specular", pointLight.phongLightProperties.specular);
    //     const auto linear = LightAttenuation::linear[pointLight.attenuationRadius];
    //     const auto quadratic = LightAttenuation::quadratic[pointLight.attenuationRadius];
    //     m_shader.setUniform(prefix + "constant", 1.0f);
    //     m_shader.setUniform(prefix + "linear", linear);
    //     m_shader.setUniform(prefix + "quadratic", quadratic);
    //
    //     ss = std::stringstream();
    //     ss << "u_pointLightPositions[" << i << "]";
    //     const auto positionPrefix = ss.str();
    //     m_shader.setUniform(positionPrefix, pointLight.position);
    // }
    //
    // MeshUtils::drawBox(m_shader, m_vao, model, m_camera.getViewMatrix(), m_camera.getProjectionMatrix());
}