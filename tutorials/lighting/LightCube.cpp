//
// Created by Patrik Aradi on 2023/12/6.
//

#include "LightCube.h"

#include "../../engine/MeshUtils.h"

LightCube::LightCube(): shader("shaders/tutorial_lighting/light_cube/vertex.glsl",
                               "shaders/tutorial_lighting/light_cube/fragment.glsl"),
                        position(0, 0, 0),
                        vao(MeshUtils::createBoxVao())
{
}

void LightCube::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = translate(modelMatrix, position);
    MeshUtils::drawBox(shader, vao, modelMatrix, viewMatrix, projectionMatrix);
}

void LightCube::setPosition(const glm::vec3& newPosition)
{
    position = newPosition;
}

const glm::vec3& LightCube::getPosition() const
{
    return position;
}
