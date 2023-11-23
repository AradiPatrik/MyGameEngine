//
// Created by Patrik Aradi on 2023/11/21.
//

#ifndef OPENGL_PLAYGROUND_GAMEBOARD_H
#define OPENGL_PLAYGROUND_GAMEBOARD_H

#include "../../engine/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameBoard {
public:
    GameBoard();

    void draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);

private:
    static GLuint createQuadVao();

    Engine::Shader shader;

    GLuint quadVao;
};


#endif //OPENGL_PLAYGROUND_GAMEBOARD_H
