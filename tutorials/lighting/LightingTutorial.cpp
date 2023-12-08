#define GL_SILENCE_DEPRECATION

#define GLFW_INCLUDE_NONE
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include "../engine/Camera.h"
#include "../engine/Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "LightCube.h"
#include "LitCube.h"
#include "../../engine/MeshUtils.h"

int main()
{
    const auto window = Engine::Window(600, 800);
    auto camera = Engine::Camera(window, true);
    camera.setPosition(glm::vec3(1.0f, 24.0f, 20.0f));
    camera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));

    auto lastFrameTime = static_cast<float>(glfwGetTime());

    LightCube light;
    light.setPosition(glm::vec3(2, 2, 2));
    LitCube litCube(glm::vec3(1.f, 0.5f, 0.38f), glm::vec3(1.0f, 1.0f, 1.0f));

    while (!window.shouldClose())
    {
        const auto thisFrameTime = static_cast<float>(glfwGetTime());
        const auto deltaTime = thisFrameTime - lastFrameTime;
        lastFrameTime = thisFrameTime;

        camera.update(deltaTime);
        glClearColor(0.5f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto viewMatrix = camera.getViewMatrix();
        auto projectionMatrix = camera.getProjectionMatrix();

        litCube.draw(viewMatrix, projectionMatrix);
        light.draw(viewMatrix, projectionMatrix);

        window.tick();
        camera.update(deltaTime);
    }

    glfwTerminate();
    return 0;
}
