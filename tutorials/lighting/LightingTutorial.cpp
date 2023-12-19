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

#include "GouraudLitCube.h"
#include "LightCube.h"
#include "LightmapCube.h"
#include "LitCube.h"
#include "MaterialCube.h"
#include "../../engine/Materials.h"

int main()
{
    const auto window = Engine::Window(600, 800);
    auto camera = Engine::Camera(window, true);
    camera.setPosition(glm::vec3(1.0f, 24.0f, 20.0f));
    camera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));

    auto lastFrameTime = static_cast<float>(glfwGetTime());

    LightCube light(PhongLightProperties(
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    ));
    GouraudLitCube gouraudCube(glm::vec3(1.f, 0.5f, 0.38f), glm::vec3(1.0f, 0.5f, 1.0f), light, camera);
    MaterialCube materialCube(glm::vec3(2.f, 0.25f, 0.8f), glm::vec3(1.0f, 0.5f, 1.0f), light, camera, emerald);
    LitCube litCube(glm::vec3(1.f, 0.5f, 0.38f), glm::vec3(1.0f, 0.5f, 1.0f), light, camera);
    LightmapCube lightmapCube(light, camera, Engine::Texture("textures/metal_container_diffuse.png"),
                              Engine::Texture("textures/metal_container_specular.png"));
    litCube.setPosition(glm::vec3(1.f, 1.f, 1.5f));
    materialCube.setPosition(glm::vec3(2.f, 2.f, 2.5f));
    lightmapCube.setPosition(glm::vec3(3.f, 3.f, 3.5f));

    while (!window.shouldClose())
    {
        const auto thisFrameTime = static_cast<float>(glfwGetTime());
        const auto deltaTime = thisFrameTime - lastFrameTime;
        lastFrameTime = thisFrameTime;

        light.setPosition(glm::vec3(sin(glfwGetTime()) * 8, 5.0, cos(glfwGetTime()) * 8));
        camera.update(deltaTime);
        glClearColor(0.5f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto viewMatrix = camera.getViewMatrix();
        auto projectionMatrix = camera.getProjectionMatrix();

        gouraudCube.draw(viewMatrix, projectionMatrix);
        light.draw(viewMatrix, projectionMatrix);
        litCube.draw(viewMatrix, projectionMatrix);
        materialCube.draw(viewMatrix, projectionMatrix);
        lightmapCube.draw(viewMatrix, projectionMatrix);

        window.tick();
        camera.update(deltaTime);
    }

    glfwTerminate();
    return 0;
}
