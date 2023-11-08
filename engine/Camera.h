//
// Created by Patrik Aradi on 2023/10/31.
//

#ifndef OPENGL_PLAYGROUND_CAMERA_H
#define OPENGL_PLAYGROUND_CAMERA_H

#include <glm/vec3.hpp>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Engine {
    class Shader;

    class Camera {
    public:
        explicit Camera(GLFWwindow *window);
        void update(float deltaTime);
        glm::mat4 getViewMatrix() const;

    private:
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 right = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
        const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        GLFWwindow *window;

        float yaw = -90.0f;
        float pitch = 0.0f;

        float lastX = 400.0f;
        float lastY = 300.0f;

        float lookSensitivity = 0.1f;
        float speed = 2.5f;
    };

} // Engine

#endif //OPENGL_PLAYGROUND_CAMERA_H
