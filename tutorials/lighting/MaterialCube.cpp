//
// Created by Patrik Aradi on 2023/12/15.
//

#include "MaterialCube.h"

#include "LightCube.h"
#include "../../engine/MeshUtils.h"
#include "../../engine/Camera.h"
#include "../../engine/Materials.h"

struct Material;

MaterialCube::MaterialCube(
    const glm::vec3& cubeColor,
    const glm::vec3& lightColor,
    const LightCube& light,
    const Camera& camera,
    const Material& material
): vao(MeshUtils::createBoxWithNormals()),
   shader(
       "shaders/tutorial_lighting/material_object/vertex.glsl",
       "shaders/tutorial_lighting/material_object/fragment.glsl"),
   position(0, 0, 0),
   cubeColor(cubeColor),
   lightColor(lightColor),
   light(light),
   camera(camera),
    material(material)
{

}

void MaterialCube::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    shader.use();
    auto modelMatrix = glm::mat4(1.0f);
    modelMatrix = translate(modelMatrix, position);
    material.bindToShader(shader);
    light.bindToShader(shader);
    shader.setUniform("u_viewPosition", camera.getPosition());
    MeshUtils::drawBox(shader, vao, modelMatrix, viewMatrix, projectionMatrix);
}

void MaterialCube::setPosition(const glm::vec3& newPosition)
{
    position = newPosition;
}
