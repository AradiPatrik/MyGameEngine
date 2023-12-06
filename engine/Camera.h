//
// Created by Patrik Aradi on 2023/10/31.
//

#ifndef OPENGL_PLAYGROUND_CAMERA_H
#define OPENGL_PLAYGROUND_CAMERA_H

#include <glm/vec3.hpp>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Window;

namespace Engine {
    class Shader;

    class Camera {
    public:
        explicit Camera(const Window &window);
        Camera(const Window &window, bool acceptsUserInput);
        void update(float deltaTime);
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix() const;

        void setPosition(const glm::vec3 &newPosition);
        void setTarget(const glm::vec3 &newTarget);

    private:
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 right = glm::vec3(0.0f, 0.0f, 0.0f);
        const glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        const Window &window;
        bool acceptsUserInput = true;

        float yaw = -90.0f;
        float pitch = 0.0f;

        float lastX = 400.0f;
        float lastY = 300.0f;

        float lookSensitivity = 0.1f;
        float speed = 2.5f;
    };

} // Engine

#endif //OPENGL_PLAYGROUND_CAMERA_H
