//
// Created by Patrik Aradi on 2023/11/23.
//

#include <GLFW/glfw3.h>
#include "../../engine/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef OPENGL_PLAYGROUND_FOOD_H
#define OPENGL_PLAYGROUND_FOOD_H

using namespace Engine;

class Food {
public:
    Food();

    void draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);

    void respawn();

    glm::vec2 getPosition();

private:
    Shader shader;

    glm::vec2 position = {0, 0};

    GLuint vao;

};


#endif //OPENGL_PLAYGROUND_FOOD_H
