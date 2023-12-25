#define GL_SILENCE_DEPRECATION

#define GLFW_INCLUDE_NONE
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <glad/glad.h>
#endif
#include "../engine/Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../engine/Materials.h"
#include "GouraudLitCube.h"
#include "LightCube.h"
#include "LightmapCube.h"
#include "LitCube.h"
#include "MaterialCube.h"
#include <GLFW/glfw3.h>

#include "../engine/Window.h"
#include "DirectionalLitCube.h"

void mapPointLightsToLightCubes(const std::vector<PointLight>& pointLights, std::vector<LightCube>& outLights)
{
    for (const auto pointLight : pointLights) {
        outLights.emplace_back(pointLight.phongLightProperties);
        outLights.back().setPosition(pointLight.position);
    }
}

int main2()
{
    const auto window = Engine::Window(600, 800);
    auto camera = Engine::Camera(window, true);
    camera.setPosition(glm::vec3(1.0f, 24.0f, 20.0f));
    camera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));

    auto lastFrameTime = static_cast<float>(glfwGetTime());

    LightCube light(PhongLightProperties(
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)));
    // GouraudLitCube gouraudCube(glm::vec3(1.f, 0.5f, 0.38f), glm::vec3(1.0f, 0.5f, 1.0f), light, camera);
    // MaterialCube materialCube(glm::vec3(2.f, 0.25f, 0.8f), glm::vec3(1.0f, 0.5f, 1.0f), light, camera, emerald);
    // LitCube litCube(glm::vec3(1.f, 0.5f, 0.38f), glm::vec3(1.0f, 0.5f, 1.0f), light, camera);
    // LightmapCube lightmapCube(light, camera, Engine::Texture("textures/metal_container_diffuse.png"),
    //     Engine::Texture("textures/metal_container_specular.png"));
    //
    DirectionLitCube directionalLitCube(light, camera, Engine::Texture("textures/metal_container_diffuse.png"),
        Engine::Texture("textures/metal_container_specular.png"),
        -glm::vec3(1.0f, 1.0f, 1.0f));


    DirectionalLight directionalLight(
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(1.0f, 1.0f, 1.0f));

    std::vector<PointLight> pointLights = {
        PointLight(glm::vec3(3, 3, 3), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1)),
        PointLight(glm::vec3(-2, 2, -2), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1)),
        PointLight(glm::vec3(-2, 2, 2), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1)),
        PointLight(glm::vec3(-2, -9, -2), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1)),
    };

    std::vector<SpotLight> spotLights;
    Engine::Texture diffuseMap("textures/metal_container_diffuse.png");
    Engine::Texture specularMap("textures/metal_container_specular.png");
    MultipleLiteCube multipleLiteCube(directionalLight, pointLights, spotLights, camera, diffuseMap, specularMap);

    multipleLiteCube.setPosition(glm::vec3(1, 1, 0));

    auto currentRotation = glm::vec3(15.f, 23.f, 42.f);

    while (!window.shouldClose()) {
        const auto thisFrameTime = static_cast<float>(glfwGetTime());
        const auto deltaTime = thisFrameTime - lastFrameTime;
        lastFrameTime = thisFrameTime;

        camera.update(deltaTime);
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentRotation.x += 2.f * deltaTime;
        currentRotation.y += 1.f * deltaTime;
        currentRotation.z += 1.f * deltaTime;

        // std::vector<LightCube> lightCubes;
        // mapPointLightsToLightCubes(pointLights, lightCubes);
        //
        // for (PointLight& pointLight : pointLights) {
        //     pointLight.position += glm::vec3(sin(glfwGetTime()) * 3, cos(glfwGetTime()) * 4, cos(glfwGetTime()) * 2) * deltaTime;
        // }
        //
        // for (const auto lightCube : lightCubes) {
        //     lightCube.draw(camera.getViewMatrix(), camera.getProjectionMatrix());
        // }
        //
        // multipleLiteCube.draw();

        light.draw(camera.getViewMatrix(), camera.getProjectionMatrix());
        directionalLitCube.draw(camera.getViewMatrix(), camera.getProjectionMatrix());

        window.tick();
        camera.update(deltaTime);
    }

    glfwTerminate();
    return 0;
}
