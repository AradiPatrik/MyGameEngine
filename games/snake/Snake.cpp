//
// Created by Patrik Aradi on 2023/11/19.
//

#include "Snake.h"

Snake::Snake(GLFWwindow *window) : window(window),
                                   shader("shaders/snake/snake/vertex.glsl", "shaders/snake/snake/fragment.glsl") {
    vao = createBoxVao();
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
        z += heading == Heading::UP ? -1.f : ((heading == Heading::DOWN) ? 1.f : 0.f);
        x += heading == Heading::RIGHT ? 1.f : ((heading == Heading::LEFT) ? -1.f : 0.f);
        timeSinceLastMove = 0.0f;
    }
}

void Snake::draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    shader.use();
    glBindVertexArray(vao);

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(x, 0, z));
    shader.setUniform("u_model", modelMatrix);
    shader.setUniform("u_view", viewMatrix);
    shader.setUniform("u_projection", projectionMatrix);
    shader.setUniform("u_borderColor", glm::vec4(0.2f, 0.4f, 0.8f, 1.0f));
    shader.setUniform("u_borderSize", 0.05f);
    shader.setUniform("u_fillColor", glm::vec4(0.4f, 0.5f, 1.0f, 1.0f));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}

GLuint Snake::createBoxVao() {
    float vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    GLuint vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(vertices),
            vertices,
            GL_STATIC_DRAW
    );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vao;
}
