//
// Created by Patrik Aradi on 2023/11/19.
//

#include "Snake.h"
#include "../../engine/MeshUtils.h"
#include "../../engine/Window.h"

Snake::Snake(const Window& window, Food& food)
    : m_shader("shaders/snake/snake/vertex.glsl",
          "shaders/snake/snake/fragment.glsl")
    , m_window(window)
    , m_food(food)
{
    m_vao = MeshUtils::createBoxVao();
}

void Snake::tick(float deltaTime)
{
    if (m_window.isKeyPressed(GLFW_KEY_W)) {
        if (m_heading != Heading::DOWN) {
            m_pendingHeading = Heading::UP;
        }
    } else if (m_window.isKeyPressed(GLFW_KEY_D)) {
        if (m_heading != Heading::LEFT) {
            m_pendingHeading = Heading::RIGHT;
        }
    } else if (m_window.isKeyPressed(GLFW_KEY_A)) {
        if (m_heading != Heading::RIGHT) {
            m_pendingHeading = Heading::LEFT;
        }
    } else if (m_window.isKeyPressed(GLFW_KEY_S)) {
        if (m_heading != Heading::UP) {
            m_pendingHeading = Heading::DOWN;
        }
    }

    const bool boosting = m_window.isKeyPressed(GLFW_KEY_LEFT_SHIFT);

    m_timeSinceLastMove += deltaTime;

    if (m_timeSinceLastMove > 1.f / (boosting ? (MOVES_PER_SECOND * 2) : MOVES_PER_SECOND)) {
        m_body.emplace_back(m_body.back());
        auto& pos = m_body.back();
        pos.y += m_pendingHeading == Heading::UP ? -1.f : ((m_pendingHeading == Heading::DOWN) ? 1.f : 0.f);
        pos.x += m_pendingHeading == Heading::RIGHT ? 1.f : ((m_pendingHeading == Heading::LEFT) ? -1.f : 0.f);
        if (pos.x == m_food.getPosition().x && pos.y == m_food.getPosition().y) {
            m_food.respawn();
        } else {
            m_body.erase(m_body.begin());

            for (auto it = m_body.begin(); it != m_body.end() - 1; it++) {
                if (it->x == pos.x && it->y == pos.y) {
                    m_body.clear();
                    m_body.emplace_back(0, 0);
                    break;
                }
            }

            auto head = m_body[m_body.size() - 1];
            if (head.x < -7 || head.y > 9 || head.x > 9 || head.y < -8) {
                m_body.clear();
                m_body.emplace_back(0, 0);
            }
        }
        m_timeSinceLastMove = 0.0f;
        m_heading = m_pendingHeading;
    }
}

void Snake::draw(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
{
    m_shader.use();
    glBindVertexArray(m_vao);
    m_shader.setUniform("u_borderColor", glm::vec4(0.2f, 0.4f, 0.8f, 1.0f));
    m_shader.setUniform("u_borderSize", 0.05f);
    m_shader.setUniform("u_fillColor", glm::vec4(0.4f, 0.5f, 1.0f, 1.0f));

    for (auto& pos : m_body) {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = translate(modelMatrix, glm::vec3(pos.x, 0.0f, pos.y));
        modelMatrix = scale(modelMatrix, glm::vec3(0.9f, 0.9f, 0.9f));
        MeshUtils::drawBox(m_shader, m_vao, modelMatrix, viewMatrix, projectionMatrix);
    }

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}
