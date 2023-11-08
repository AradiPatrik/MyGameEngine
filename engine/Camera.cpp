//
// Created by Patrik Aradi on 2023/10/31.
//

#include "Camera.h"
#include "Shader.h"

namespace Engine {
    Camera::Camera(GLFWwindow *window) : window(window) {}

    void Camera::update(const float deltaTime) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            position += front * deltaTime * speed;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            position -= front * deltaTime * speed;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            position -= right * deltaTime * speed;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            position += right * deltaTime * speed;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float xOffset = static_cast<float>(mouseX) - lastX;
        float yOffset = lastY - static_cast<float>(mouseY);

        lastX = static_cast<float>(mouseX);
        lastY = static_cast<float>(mouseY);

        xOffset *= lookSensitivity;
        yOffset *= lookSensitivity;

        yaw += xOffset;
        pitch += yOffset;

        if (pitch > 89.0f) {
            pitch = 89.0f;
        }

        if (pitch < -89.0f) {
            pitch = -89.0f;
        }

        glm::mat4 rotationMatrix = glm::mat4(1.0f);
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(-yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::vec3 direction = glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
        front = glm::normalize(direction);
        right = glm::normalize(glm::cross(front, up));
    }

    glm::mat4 Camera::getViewMatrix() const {
        glm::mat4 view = glm::mat4(1.0f);
        return glm::lookAt(
                position,
                position + front,
                up
        );
    }


} // Engine