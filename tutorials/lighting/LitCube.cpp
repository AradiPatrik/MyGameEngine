//
// Created by Patrik Aradi on 2023/12/8.
//

#include "LitCube.h"

#include "LightCube.h"
#include "../../engine/Camera.h"
#include "../../engine/MeshUtils.h"

namespace Engine
{
    class Camera;
}

LitCube::LitCube(const glm::vec3& cubeColor, const glm::vec3& lightColor, const LightCube& light, const Camera& camera):
    vao(MeshUtils::createBoxWithNormals()),
    shader(
        "shaders/tutorial_lighting/object/vertex.glsl",
        "shaders/tutorial_lighting/object/fragment.glsl"),
    position(0, 0, 0),
    cubeColor(cubeColor),
    lightColor(lightColor),
    light(light),
    camera(camera)
{
}

void LitCube::draw(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
{
    shader.use();
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = translate(modelMatrix, position);
    shader.setUniform("u_lightPosition", light.getPosition());
    shader.setUniform("u_viewPosition", camera.getPosition());
    shader.setUniform("u_objectColor", cubeColor);
    shader.setUniform("u_lightColor", lightColor);
    MeshUtils::drawBox(shader, vao, modelMatrix, viewMatrix, projectionMatrix);
}
