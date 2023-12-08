//
// Created by Patrik Aradi on 2023/12/8.
//

#include "LitCube.h"

#include "../../engine/MeshUtils.h"

LitCube::LitCube(const glm::vec3& cubeColor, const glm::vec3& lightColor):
    vao(MeshUtils::createBoxVao()),
    shader(
        "shaders/tutorial_lighting/object/vertex.glsl",
        "shaders/tutorial_lighting/object/fragment.glsl"),
    position(0, 0, 0),
    cubeColor(cubeColor),
    lightColor(lightColor)
{
}

void LitCube::draw(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
{
    shader.use();
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = translate(modelMatrix, position);
    shader.setUniform("u_objectColor", cubeColor);
    shader.setUniform("u_lightColor", lightColor);
    MeshUtils::drawBox(shader, vao, modelMatrix, viewMatrix, projectionMatrix);
}
