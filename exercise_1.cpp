#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include "engine/Shader.h"
#include <fstream>

void onResizeWindow(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(
            800,
            600,
            "LearnOpenGL",
            nullptr,
            nullptr
    );

    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, onResizeWindow);

    GLfloat vertices[] = {
            -0.5f, 0.5f, 0.0f, // left top
            -1.0f, -0.5f, 0.0f, // left bottom left
            0.0f, -0.5f, 0.0f, // left bottom right
            0.5f, 0.5f, 0.0f, // right top
            1.0f, -0.5f, 0.0f, // right bottom left
            0.0f, -0.5f, 0.0f, // right bottom right
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

    const auto simpleShader = Engine::Shader("shaders/simple_vertex.glsl", "shaders/simple_fragment.glsl");

    const auto redShader = Engine::Shader("shaders/simple_vertex.glsl", "shaders/exercise_01/red_fragment.glsl");

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);

    float boxVertices[] = {
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
    };

    GLuint boxIndices[] = {
            0, 1, 3,
            1, 2, 3
    };

    GLuint boxVao;
    glGenVertexArrays(1, &boxVao);

    GLuint boxVbo;
    glGenBuffers(1, &boxVbo);

    GLuint boxEbo;
    glGenBuffers(1, &boxEbo);

    glBindVertexArray(boxVao);
    glBindBuffer(GL_ARRAY_BUFFER, boxVbo);
    glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(boxVertices),
            boxVertices,
            GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxEbo);
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            sizeof(boxIndices),
            boxIndices,
            GL_STATIC_DRAW
    );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLuint leftTriangleVao;
    glGenVertexArrays(1, &leftTriangleVao);

    GLfloat leftTriangleVertices[] = {
            -0.5f, 0.5f, 0.0f, // left top
            -1.0f, -0.5f, 0.0f, // left bottom left
            0.0f, -0.5f, 0.0f, // left bottom right
    };

    glBindVertexArray(leftTriangleVao);

    GLuint leftTriangleVbo;
    glGenBuffers(1, &leftTriangleVbo);

    glBindBuffer(GL_ARRAY_BUFFER, leftTriangleVbo);
    glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(leftTriangleVertices),
            leftTriangleVertices,
            GL_STATIC_DRAW
    );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLfloat rightTriangleVertices[] = {
            0.0f, -0.5f, 0.0f, // right bottom right
            0.5f, 0.5f, 0.0f, // right top
            1.0f, -0.5f, 0.0f, // right bottom left
    };

    GLuint rightTriangleVao;
    glGenVertexArrays(1, &rightTriangleVao);

    GLuint rightTriangleVbo;
    glGenBuffers(1, &rightTriangleVbo);

    glBindVertexArray(rightTriangleVao);
    glBindBuffer(GL_ARRAY_BUFFER, rightTriangleVbo);

    glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(rightTriangleVertices),
            rightTriangleVertices,
            GL_STATIC_DRAW
    );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        simpleShader.use();
        glBindVertexArray(leftTriangleVao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        redShader.use();
        glBindVertexArray(rightTriangleVao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
