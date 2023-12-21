//
// Created by Patrik Aradi on 2023/12/18.
//

#include "LightmapCube.h"
#include "../../engine/Camera.h"
#include "../../engine/MeshUtils.h"
#include "LightCube.h"

struct Material;

LightmapCube::LightmapCube(
    const LightCube& light,
    const Camera& camera,
    const Texture& diffuseMap,
    const Texture& specularMap)
    : m_vao(MeshUtils::createBoxWithNormalsAndUvs())
    , m_shader(
          "shaders/tutorial_lighting/light_map_object/vertex.glsl",
          "shaders/tutorial_lighting/light_map_object/fragment.glsl")
    , m_position(0, 0, 0)
    , m_light(light)
    , m_camera(camera)
    , m_diffuseMap(diffuseMap)
    , m_specularMap(specularMap)
{
}

void LightmapCube::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    m_shader.use();
    auto modelMatrix = glm::mat4(1.0f);
    modelMatrix = translate(modelMatrix, m_position);
    modelMatrix = rotate(modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = rotate(modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = rotate(modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    m_light.bindToShader(m_shader);
    m_diffuseMap.bind(m_shader, GL_TEXTURE0, "u_material.diffuse");
    m_specularMap.bind(m_shader, GL_TEXTURE1, "u_material.specular");
    m_shader.setUniform("u_material.shininess", 32.0f);
    m_shader.setUniform("u_viewPosition", m_camera.getPosition());
    MeshUtils::drawBox(m_shader, m_vao, modelMatrix, viewMatrix, projectionMatrix);
}

void LightmapCube::setPosition(const glm::vec3& newPosition)
{
    m_position = newPosition;
}

void LightmapCube::setRotation(const glm::vec3& newRotation)
{
    m_rotation = newRotation;
}
