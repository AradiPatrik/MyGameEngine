//
// Created by Patrik Aradi on 2023/12/22.
//

#include "../../engine/Camera.h"
#include "../../engine/Materials.h"
#include "../../engine/MeshUtils.h"
#include "../../engine/Window.h"
#include "../lighting/LightCube.h"
#include "../lighting/LitCube.h"
#include "../lighting/MaterialCube.h"
#include "GLFW/glfw3.h"

#include <iostream>

int main()
{
    Window window(800, 600);

    LightCube lightCube(PhongLightProperties(glm::vec3(1.0f), glm::vec3(1.0), glm::vec3(1.0f)));
    lightCube.setPosition(glm::vec3(3.0, 3.0, 3.0));
    Camera camera(window, true);
    camera.setPosition(glm::vec3(5, 5, 5));
    camera.setTarget(glm::vec3(0, 0, 0));
    MaterialCube materialCube(glm::vec3(2.f, 0.25f, 0.8f), glm::vec3(1.0f, 0.5f, 1.0f), lightCube, camera, emerald);
    materialCube.setPosition(glm::vec3(0, 0, 0));

    auto lastFrameTime = static_cast<float>(glfwGetTime());
    glClearColor(0.5, 0.5, 0.5, 1.0);
    while (!window.shouldClose()) {
        auto thisFrameTime = static_cast<float>(glfwGetTime());
        auto deltaTime = thisFrameTime - lastFrameTime;
        lastFrameTime = thisFrameTime;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        camera.update(deltaTime);
        materialCube.draw(camera.getViewMatrix(), camera.getProjectionMatrix());
        lightCube.draw(camera.getViewMatrix(), camera.getProjectionMatrix());

        window.tick();
    }

    return 0;
}