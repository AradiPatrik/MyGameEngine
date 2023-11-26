//
// Created by Patrik Aradi on 2023/11/21.
//

#include "GameBoard.h"
#include "../../engine/MeshUtils.h"
#include "glm/gtx/transform.hpp"

GameBoard::GameBoard():
    shader("shaders/snake/gameboard/vertex.glsl", "shaders/snake/gameboard/fragment.glsl"),
    wallShader("shaders/snake/snake/vertex.glsl", "shaders/snake/snake/fragment.glsl")
{
    quadVao = MeshUtils::createQuadVao();
    boxVao = MeshUtils::createBoxVao();
}

void GameBoard::draw(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
{
    shader.use();
    shader.setUniform("u_borderColor", glm::vec4(0.4f, 0.8f, 0.4f, 1.0f));
    shader.setUniform("u_borderSize", 0.05f);
    shader.setUniform("u_fillColor", glm::vec4(0.1f, 0.5f, 0.5f, 1.0f));

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = rotate(modelMatrix, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
    modelMatrix = scale(modelMatrix, glm::vec3(10.f, 10.f, 1.f));
    modelMatrix = translate(modelMatrix, glm::vec3(0.1f, -0.1f, 0.5f));

    MeshUtils::drawQuad(shader, quadVao, modelMatrix, viewMatrix, projectionMatrix);

    wallShader.use();
    wallShader.setUniform("u_borderColor", glm::vec4(0.2f, 0.4f, 0.8f, 1.0f));
    wallShader.setUniform("u_borderSize", 0.05f);
    wallShader.setUniform("u_fillColor", glm::vec4(0.45f, 0.80f, 0.33f, 1.0f));
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = translate(modelMatrix, glm::vec3(1.f, 0.0f, 9.5f));
    modelMatrix = scale(modelMatrix, glm::vec3(20.f, 1.f, 1.f));

    MeshUtils::drawBox(wallShader, boxVao, modelMatrix, viewMatrix, projectionMatrix);

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = translate(modelMatrix, glm::vec3(1.f, 0.f, -9.5f));
    modelMatrix = scale(modelMatrix, glm::vec3(20.f, 1.f, 1.f));

    MeshUtils::drawBox(wallShader, boxVao, modelMatrix, viewMatrix, projectionMatrix);

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = translate(modelMatrix, glm::vec3(10.5f, 0.0f, 0.f));
    modelMatrix = rotate(modelMatrix, glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f));
    modelMatrix = scale(modelMatrix, glm::vec3(20.f, 1.f, 1.f));

    MeshUtils::drawBox(wallShader, boxVao, modelMatrix, viewMatrix, projectionMatrix);

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = translate(modelMatrix, glm::vec3(-8.5f, 0.0f, 0.f));
    modelMatrix = rotate(modelMatrix, glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f));
    modelMatrix = scale(modelMatrix, glm::vec3(20.f, 1.f, 1.f));

    MeshUtils::drawBox(wallShader, boxVao, modelMatrix, viewMatrix, projectionMatrix);
}
