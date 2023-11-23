//
// Created by Patrik Aradi on 2023/11/19.
//

#include "Snake.h"
#include "MeshUtils.h"

Snake::Snake(GLFWwindow *window, Food &food) : window(window),
                                               shader("shaders/snake/snake/vertex.glsl",
                                                      "shaders/snake/snake/fragment.glsl"),
                                               food(food) {
    vao = MeshUtils::createBoxVao();
}

void Snake::tick(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (heading != Heading::DOWN) {
            pendingHeading = Heading::UP;
        }
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (heading != Heading::LEFT) {
            pendingHeading = Heading::RIGHT;
        }
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (heading != Heading::RIGHT) {
            pendingHeading = Heading::LEFT;
        }
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (heading != Heading::UP) {
            pendingHeading = Heading::DOWN;
        }
    }

    bool boosting = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;

    timeSinceLastMove += deltaTime;

    if (timeSinceLastMove > 1.f / (boosting ? (MOVES_PER_SECOND * 2) : MOVES_PER_SECOND)) {
        body.emplace_back(body.back());
        auto &pos = body.back();
        pos.y += pendingHeading == Heading::UP ? -1.f : ((pendingHeading == Heading::DOWN) ? 1.f : 0.f);
        pos.x += pendingHeading == Heading::RIGHT ? 1.f : ((pendingHeading == Heading::LEFT) ? -1.f : 0.f);
        if (pos.x == food.getPosition().x && pos.y == food.getPosition().y) {
            food.respawn();
        } else {
            body.erase(body.begin());

            for (auto it = body.begin(); it != body.end() - 1; it++) {
                if (it->x == pos.x && it->y == pos.y) {
                    body.clear();
                    body.emplace_back(0, 0);
                    break;
                }
            }
        }
        timeSinceLastMove = 0.0f;
        heading = pendingHeading;
    }
}

void Snake::draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    shader.use();
    glBindVertexArray(vao);
    shader.setUniform("u_borderColor", glm::vec4(0.2f, 0.4f, 0.8f, 1.0f));
    shader.setUniform("u_borderSize", 0.05f);
    shader.setUniform("u_fillColor", glm::vec4(0.4f, 0.5f, 1.0f, 1.0f));

    for (auto &pos: body) {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(pos.x, 0.0f, pos.y));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.9f, 0.9f, 0.9f));
        MeshUtils::drawBox(shader, vao, modelMatrix, viewMatrix, projectionMatrix);
    }

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}
