//
// Created by Patrik Aradi on 2023/12/6.
//

#ifndef WINDOW_H
#define WINDOW_H


class Window {
public:
    Window(int width, int height);
    bool shouldClose() const;
    void tick() const;
    bool isKeyPressed(int glfwKeyCode) const;
    void getCursorPosition(double &outMouseX, double &outMouseY) const;

private:
    int width;
    int height;
    class GLFWwindow *window;
};


#endif //WINDOW_H
