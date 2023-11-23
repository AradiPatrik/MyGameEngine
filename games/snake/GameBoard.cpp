//
// Created by Patrik Aradi on 2023/11/21.
//

#include "GameBoard.h"
#include "MeshUtils.h"

GameBoard::GameBoard(): shader("shaders/snake/gameboard/vertex.glsl", "shaders/snake/gameboard/fragment.glsl") {
    quadVao = MeshUtils::createQuadVao();
}

void GameBoard::draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    shader.use();
    shader.setUniform("u_borderColor", glm::vec4(0.4f, 0.8f, 0.4f, 1.0f));
    shader.setUniform("u_borderSize", 0.05f);
    shader.setUniform("u_fillColor", glm::vec4(0.1f, 0.5f, 0.5f, 1.0f));

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(10.f, 10.f, 1.f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.1f, -0.1f, 0.5f));

    MeshUtils::drawQuad(shader, quadVao, modelMatrix, viewMatrix, projectionMatrix);

    glBindVertexArray(quadVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
