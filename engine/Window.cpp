//
// Created by Patrik Aradi on 2023/12/6.
//

#include "Window.h"

#include <iostream>
#ifdef _WIN32
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

namespace Engine
{
    Window::Window(const int width, const int height): width(width), height(height)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(
            800,
            600,
            "LearnOpenGL",
            nullptr,
            nullptr
        );

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (window == nullptr)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window);

        int initialFrameBufferWidth, initialFrameBufferHeight;
        glfwGetFramebufferSize(window, &initialFrameBufferWidth, &initialFrameBufferHeight);

#ifndef __APPLE__
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
#endif

        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int newWidth, int newHeight)
        {
            glViewport(0, 0, newWidth, newHeight);
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            {
                glfwSetWindowShouldClose(window, true);
            }
        });

        glViewport(0, 0, initialFrameBufferWidth, initialFrameBufferHeight);
        glEnable(GL_DEPTH_TEST);
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(window);
    }

    void Window::tick() const
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    bool Window::isKeyPressed(const int glfwKeyCode) const
    {
        return glfwGetKey(window, glfwKeyCode) == GLFW_PRESS;
    }

    void Window::getCursorPosition(double& outMouseX, double& outMouseY) const
    {
        glfwGetCursorPos(window, &outMouseX, &outMouseY);
    }

}
