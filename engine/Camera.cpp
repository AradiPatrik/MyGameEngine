//
// Created by Patrik Aradi on 2023/10/31.
//

#include "Camera.h"
#include "Shader.h"
#include "Window.h"

class Window;

namespace Engine
{
    Camera::Camera(const Window& window, bool acceptsUserInput) : window(window), acceptsUserInput(acceptsUserInput)
    {
    }

    void Camera::update(const float deltaTime)
    {
        if (acceptsUserInput)
        {
            if (window.isKeyPressed(GLFW_KEY_W))
            {
                position += front * deltaTime * speed;
            }

            if (window.isKeyPressed(GLFW_KEY_S))
            {
                position -= front * deltaTime * speed;
            }

            if (window.isKeyPressed(GLFW_KEY_A))
            {
                position -= right * deltaTime * speed;
            }

            if (window.isKeyPressed(GLFW_KEY_D))
            {
                position += right * deltaTime * speed;
            }

            double mouseX, mouseY;
            window.getCursorPosition(mouseX, mouseY);

            float xOffset = static_cast<float>(mouseX) - lastX;
            float yOffset = lastY - static_cast<float>(mouseY);

            lastX = static_cast<float>(mouseX);
            lastY = static_cast<float>(mouseY);

            xOffset *= lookSensitivity;
            yOffset *= lookSensitivity;

            yaw += xOffset;
            pitch += yOffset;

            if (pitch > 89.0f)
            {
                pitch = 89.0f;
            }

            if (pitch < -89.0f)
            {
                pitch = -89.0f;
            }
        }

        glm::vec3 direction = glm::vec3(
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        );
        front = normalize(direction);
        right = normalize(cross(front, up));
    }

    glm::mat4 Camera::getViewMatrix() const
    {
        glm::mat4 view = glm::mat4(1.0f);
        return lookAt(
            position,
            position + front,
            up
        );
    }

    void Camera::setPosition(const glm::vec3& newPosition)
    {
        position = newPosition;
    }

    Camera::Camera(const Window& window): Camera(window, true)
    {
    }

    glm::mat4 Camera::getProjectionMatrix() const
    {
        return projectionMatrix;
    }

    void Camera::setTarget(const glm::vec3& newTarget)
    {
        front = normalize(newTarget - position);

        pitch = glm::degrees(asin(front.y));
        //        yaw = glm::degrees(atan2(front.x, front.z));
    }

    const glm::vec3& Camera::getPosition() const
    {
        return position;
    }
} // Engine
