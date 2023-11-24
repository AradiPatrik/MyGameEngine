//
// Created by Patrik Aradi on 2023/11/23.
//

#ifndef OPENGL_PLAYGROUND_MESHUTILS_H
#define OPENGL_PLAYGROUND_MESHUTILS_H

#include <GLFW/glfw3.h>
#include "../../engine/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Engine;

namespace MeshUtils
{
    GLuint createQuadVao();

    GLuint createBoxVao();

    void drawQuad(Shader& shader, GLuint vao, glm::mat4& modelMatrix, glm::mat4& viewMatrix,
                  glm::mat4& projectionMatrix);

    void drawBox(Shader& shader, GLuint vao, glm::mat4& modelMatrix, glm::mat4& viewMatrix,
                 glm::mat4& projectionMatrix);
}


#endif //OPENGL_PLAYGROUND_MESHUTILS_H
