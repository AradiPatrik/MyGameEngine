//
// Created by Patrik Aradi on 2023/11/23.
//

#include "Food.h"
#include "MeshUtils.h"

Food::Food(): shader("shaders/snake/food/vertex.glsl", "shaders/snake/food/fragment.glsl") {
    vao = MeshUtils::createBoxVao();
    respawn();
}

void Food::draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    shader.use();
    shader.setUniform("u_fillColor", glm::vec4(0.8f, 0.5f, 0.5f, 1.0f));
    shader.setUniform("u_borderColor", glm::vec4(0.8f, 0.2f, 0.2f, 1.0f));
    shader.setUniform("u_borderSize", 0.05f);

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(position.x, 0.f,  position.y));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.9f, 0.9f, 0.9f));

    MeshUtils::drawBox(shader, vao, modelMatrix, viewMatrix, projectionMatrix);
}

void Food::respawn() {
    position.x = (rand() % 20) - 10;
    position.y = (rand() % 20) - 10;
}

glm::vec2 Food::getPosition() {
    return position;
}

