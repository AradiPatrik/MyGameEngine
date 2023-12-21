//
// Created by Patrik Aradi on 2023/11/19.
//

#ifndef OPENGL_PLAYGROUND_SNAKE_H
#define OPENGL_PLAYGROUND_SNAKE_H

#include <vector>
#define GLFW_INCLUDE_NONE
#include "../../engine/Shader.h"
#include "Food.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
class Window;
}

using namespace Engine;

class Snake {
public:
    explicit Snake(const Window& window, Food& food);

    void tick(float deltaTime);
    void draw(glm::mat4& viewMatrix, glm::mat4& projectionMatrix);

    enum class Heading {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

private:
    Shader m_shader;

    std::vector<glm::vec2> m_body = { { 0, 0 } };

    Heading m_heading = Heading::UP;
    Heading m_pendingHeading = Heading::UP;

    float m_timeSinceLastMove = 0.0f;

    const Window& m_window;

    GLuint m_vao;

    Food& m_food;

    static constexpr int MOVES_PER_SECOND = 5;
};

#endif // OPENGL_PLAYGROUND_SNAKE_H
