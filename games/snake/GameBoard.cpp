//
// Created by Patrik Aradi on 2023/11/21.
//

#include "GameBoard.h"

GameBoard::GameBoard(): shader("shaders/snake/gameboard/vertex.glsl", "shaders/snake/gameboard/fragment.glsl") {
    quadVao = createQuadVao();
}

GLuint GameBoard::createQuadVao() {
    GLfloat vertices[] = {
            -1.f, 1.f, 0.0f, 0.0f, 1.0f,
            1.f, 1.f, 0.0f, 1.0f, 1.0f,
            1.f, -1.f, 0.0f, 1.0f, 0.0f,
            1.f, -1.f, 0.0f, 1.0f, 0.0f,
            -1.f, -1.f, 0.0f, 0.0f, 0.0f,
            -1.f, 1.f, 0.0f, 0.0f, 1.0f
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(vertices),
            vertices,
            GL_STATIC_DRAW
    );

    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            5 * sizeof(GLfloat),
            (GLvoid *) 0
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
            1,
            2,
            GL_FLOAT,
            GL_FALSE,
            5 * sizeof(GLfloat),
            (GLvoid *) (3 * sizeof(GLfloat))
    );
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    return vao;
}

void GameBoard::draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix) {
    shader.use();

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(10.f, 10.f, 1.f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.1f, -0.1f, 0.5f));
    shader.setUniform("u_model", modelMatrix);


    shader.setUniform("u_model", modelMatrix);
    shader.setUniform("u_view", viewMatrix);
    shader.setUniform("u_projection", projectionMatrix);
    shader.setUniform("u_borderColor", glm::vec4(0.4f, 0.8f, 0.4f, 1.0f));
    shader.setUniform("u_borderSize", 0.05f);
    shader.setUniform("u_fillColor", glm::vec4(0.1f, 0.5f, 0.5f, 1.0f));

    glBindVertexArray(quadVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
