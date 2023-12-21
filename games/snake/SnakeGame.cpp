#define GL_SILENCE_DEPRECATION

#define GLFW_INCLUDE_NONE
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <glad/glad.h>
#endif
#include "../../engine/Camera.h"
#include "../../engine/Shader.h"
#include "GameBoard.h"
#include "Snake.h"
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "../../engine/Window.h"

int main()
{
    Window window(800, 600);

    Food food;
    Snake snake(window, food);
    GameBoard gameBoard;

    stbi_set_flip_vertically_on_load(true);

    auto camera = Camera(window, false);
    camera.setPosition(glm::vec3(1.0f, 24.0f, 20.0f));
    camera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));

    auto lastFrameTime = static_cast<float>(glfwGetTime());

    while (!window.shouldClose()) {
        const auto thisFrameTime = static_cast<float>(glfwGetTime());
        const auto deltaTime = thisFrameTime - lastFrameTime;
        lastFrameTime = thisFrameTime;

        camera.update(deltaTime);

        glClearColor(0.5f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        snake.tick(deltaTime);
        auto viewMatrix = camera.getViewMatrix();
        auto projectionMatrix = camera.getProjectionMatrix();
        snake.draw(viewMatrix, projectionMatrix);
        gameBoard.draw(viewMatrix, projectionMatrix);
        food.draw(viewMatrix, projectionMatrix);

        window.tick();
    }

    glfwTerminate();
    return 0;
}
