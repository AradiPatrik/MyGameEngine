//
// Created by Patrik Aradi on 2023/11/19.
//

#ifndef OPENGL_PLAYGROUND_SNAKE_H
#define OPENGL_PLAYGROUND_SNAKE_H

#include <GLFW/glfw3.h>
#include "../../engine/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Engine;

class Snake {
public:
    explicit Snake(GLFWwindow *window);

    void tick(float deltaTime);
    void draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);

    enum class Heading {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
private:
    Shader shader;

    std::vector<glm::vec2> body = {{0, 0}};

    Heading heading = Heading::UP;

    float timeSinceLastMove = 0.0f;

    GLFWwindow *window;

    GLuint vao;

    static GLuint createBoxVao();

    static const int MOVES_PER_SECOND = 2;
};


#endif //OPENGL_PLAYGROUND_SNAKE_H
