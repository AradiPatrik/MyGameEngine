#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include "engine/Shader.h"
#include "stb_image.h"
#include "engine/Texture.h"

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

    const auto shader = Engine::Shader("shaders/texture_lesson/vertex_ct.glsl",
                                       "shaders/texture_lesson/fragment_ct.glsl");

    float boxVertices[] = {
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom left
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // top left
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    stbi_set_flip_vertically_on_load(true);

    const auto texture0 = Engine::Texture("textures/wooden_container.png");
    const auto texture1 = Engine::Texture("textures/smile.png");

    texture0.bind(GL_TEXTURE0);
    texture1.bind(GL_TEXTURE1);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.setUniform("texture1", 0);
        shader.setUniform("texture2", 1);

        shader.use();

        glBindVertexArray(boxVao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
