//
// Created by Patrik Aradi on 2023/12/22.
//

#include "../../engine/Camera.h"
#include "../../engine/Materials.h"
#include "../../engine/Model.h"
#include "../../engine/Window.h"
#include "../lighting/LightCube.h"
#include "../lighting/LitCube.h"
#include "../lighting/MaterialCube.h"
#include "GLFW/glfw3.h"

#ifdef WIN32
#include <glad/glad.h>
#endif

#include <iostream>

int main()
{
    Engine::Window window(800, 600);
    glEnable(GL_STENCIL_TEST);

    LightCube lightCube(PhongLightProperties(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f)));
    lightCube.setPosition(glm::vec3(3.0, 3.0, 3.0));
    Engine::Camera camera(window, true);
    camera.setPosition(glm::vec3(5, 5, 5));
    camera.setTarget(glm::vec3(0, 0, 0));

    auto lastFrameTime = static_cast<float>(glfwGetTime());

    Engine::Shader textureDebugShader("shaders/texture_debug_shader/vertex.glsl", "shaders/texture_debug_shader/fragment.glsl");

    Engine::Shader shader("shaders/tutorial_lighting/multiple_light_shader/vertex.glsl",
        "shaders/tutorial_lighting/multiple_light_shader/fragment.glsl");

    Engine::Shader outlineShader("shaders/stencil/vertex.glsl",
        "shaders/stencil/fragment.glsl");
    outlineShader.use();
    outlineShader.setUniform("u_outline", 0.1f);
    outlineShader.setUniform("u_outlineColor", glm::vec3(1.0f, 0.8f, 0.4f));

    DirectionalLight directionalLight(glm::vec3(1.0f), glm::vec3(0.05f), glm::vec3(0.2f), glm::vec3(0.4f));

    Engine::Model model("assets/models/survival_backpack/backpack.obj");
    Engine::Model model2("assets/models/evil_chest/untitled.obj");


    glClearColor(0.1, 0.1, 0.1, 1.0);

    while (!window.shouldClose()) {
        auto thisFrameTime = static_cast<float>(glfwGetTime());
        auto deltaTime = thisFrameTime - lastFrameTime;
        lastFrameTime = thisFrameTime;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        camera.update(deltaTime);
        camera.bindViewAndProjectionMatrix(shader);
        camera.bindViewAndProjectionMatrix(textureDebugShader);
        camera.bindViewAndProjectionMatrix(outlineShader);

        lightCube.setPosition(glm::vec3(5.0 * sin(thisFrameTime), 3.0, 5.0 * cos(thisFrameTime)));

        lightCube.bindToShader(shader, 0);

        auto modelMatrix = glm::mat4(1.0f);
        modelMatrix = translate(modelMatrix, glm::vec3(0.0f, 2, 0.0f));
        shader.use();
        shader.setUniform("u_model", modelMatrix);
        shader.setUniform("u_pointLightCount", 1);

        shader.use();
        shader.setUniform("u_directionalLightDirection", glm::vec3(1.0f, 2.0f, 3.0f));
        shader.setUniform("u_directionalLight.ambient", directionalLight.phongLightProperties.ambient);
        shader.setUniform("u_directionalLight.diffuse", directionalLight.phongLightProperties.diffuse);
        shader.setUniform("u_directionalLight.specular", directionalLight.phongLightProperties.specular);
        shader.setUniform("u_material.shininess", 32.0f);

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        model.draw(shader);

        glStencilMask(0x00);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        outlineShader.use();
        outlineShader.setUniform("u_model", modelMatrix);
        model.draw(outlineShader);

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

        modelMatrix = glm::mat4(1.0f);
        modelMatrix = translate(modelMatrix, glm::vec3(3.0f, 0, 3.0f));
        shader.use();
        shader.setUniform("u_model", modelMatrix);
        model2.draw(shader);

        lightCube.draw(camera.getViewMatrix(), camera.getProjectionMatrix());

        window.tick();
    }

    // check gl erros
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;
    }
    return 0;
}