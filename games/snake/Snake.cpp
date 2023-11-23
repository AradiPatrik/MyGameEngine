//
// Created by Patrik Aradi on 2023/11/19.
//

#include "Snake.h"
#include "MeshUtils.h"

Snake::Snake(GLFWwindow *window) : window(window),
                                   shader("shaders/snake/snake/vertex.glsl", "shaders/snake/snake/fragment.glsl") {
    vao = MeshUtils::createBoxVao();
}

void Snake::tick(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        heading = Heading::UP;
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        heading = Heading::RIGHT;
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        heading = Heading::LEFT;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        heading = Heading::DOWN;
    }

    timeSinceLastMove += deltaTime;

    if (timeSinceLastMove > 1.f / MOVES_PER_SECOND) {
        body.emplace_back(body.back());
        body.erase(body.begin());
        auto &pos = body.back();
        pos.y += heading == Heading::UP ? -1.f : ((heading == Heading::DOWN) ? 1.f : 0.f);
        pos.x += heading == Heading::RIGHT ? 1.f : ((heading == Heading::LEFT) ? -1.f : 0.f);
        timeSinceLastMove = 0.0f;
    }
}

void Snake::draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    shader.use();
    glBindVertexArray(vao);
    shader.setUniform("u_borderColor", glm::vec4(0.2f, 0.4f, 0.8f, 1.0f));
    shader.setUniform("u_borderSize", 0.05f);
    shader.setUniform("u_fillColor", glm::vec4(0.4f, 0.5f, 1.0f, 1.0f));

    for (auto &pos : body) {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(pos.x, 0.0f, pos.y));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.9f, 0.9f, 0.9f));
        MeshUtils::drawBox(shader, vao, modelMatrix, viewMatrix, projectionMatrix);
    }

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}
