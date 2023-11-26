//
// Created by Patrik Aradi on 2023/11/21.
//

#ifndef OPENGL_PLAYGROUND_GAMEBOARD_H
#define OPENGL_PLAYGROUND_GAMEBOARD_H

#include "../../engine/Shader.h"
#include <glm/glm.hpp>

class GameBoard {
public:
    GameBoard();

    void draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);

private:
    Engine::Shader shader;

    Engine::Shader wallShader;

    GLuint quadVao;
    GLuint boxVao;
};


#endif //OPENGL_PLAYGROUND_GAMEBOARD_H
