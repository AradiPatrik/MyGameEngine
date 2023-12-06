//
// Created by Patrik Aradi on 2023/11/19.
//

#include "Snake.h"
#include "../../engine/MeshUtils.h"
#include "../../engine/Window.h"

Snake::Snake(const Window& window, Food& food) : window(window),
                                                 shader("shaders/snake/snake/vertex.glsl",
                                                        "shaders/snake/snake/fragment.glsl"),
                                                 food(food)
{
    vao = MeshUtils::createBoxVao();
}

void Snake::tick(float deltaTime)
{
    if (window.isKeyPressed(GLFW_KEY_W))
    {
        if (heading != Heading::DOWN)
        {
            pendingHeading = Heading::UP;
        }
    }
    else if (window.isKeyPressed(GLFW_KEY_D))
    {
        if (heading != Heading::LEFT)
        {
            pendingHeading = Heading::RIGHT;
        }
    }
    else if (window.isKeyPressed(GLFW_KEY_A))
    {
        if (heading != Heading::RIGHT)
        {
            pendingHeading = Heading::LEFT;
        }
    }
    else if (window.isKeyPressed(GLFW_KEY_S))
    {
        if (heading != Heading::UP)
        {
            pendingHeading = Heading::DOWN;
        }
    }

    const bool boosting = window.isKeyPressed(GLFW_KEY_LEFT_SHIFT);

    timeSinceLastMove += deltaTime;

    if (timeSinceLastMove > 1.f / (boosting ? (MOVES_PER_SECOND * 2) : MOVES_PER_SECOND))
    {
        body.emplace_back(body.back());
        auto& pos = body.back();
        pos.y += pendingHeading == Heading::UP ? -1.f : ((pendingHeading == Heading::DOWN) ? 1.f : 0.f);
        pos.x += pendingHeading == Heading::RIGHT ? 1.f : ((pendingHeading == Heading::LEFT) ? -1.f : 0.f);
        if (pos.x == food.getPosition().x && pos.y == food.getPosition().y)
        {
            food.respawn();
        }
        else
        {
            body.erase(body.begin());

            for (auto it = body.begin(); it != body.end() - 1; it++)
            {
                if (it->x == pos.x && it->y == pos.y)
                {
                    body.clear();
                    body.emplace_back(0, 0);
                    break;
                }
            }

            auto head = body[body.size() - 1];
            if (head.x < -7 || head.y > 9 || head.x > 9 || head.y < -8)
            {
                body.clear();
                body.emplace_back(0, 0);
            }
        }
        timeSinceLastMove = 0.0f;
        heading = pendingHeading;
    }
}

void Snake::draw(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
{
    shader.use();
    glBindVertexArray(vao);
    shader.setUniform("u_borderColor", glm::vec4(0.2f, 0.4f, 0.8f, 1.0f));
    shader.setUniform("u_borderSize", 0.05f);
    shader.setUniform("u_fillColor", glm::vec4(0.4f, 0.5f, 1.0f, 1.0f));

    for (auto& pos : body)
    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = translate(modelMatrix, glm::vec3(pos.x, 0.0f, pos.y));
        modelMatrix = scale(modelMatrix, glm::vec3(0.9f, 0.9f, 0.9f));
        MeshUtils::drawBox(shader, vao, modelMatrix, viewMatrix, projectionMatrix);
    }

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}
