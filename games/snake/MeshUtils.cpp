//
// Created by Patrik Aradi on 2023/11/23.
//

#include "MeshUtils.h"

GLuint MeshUtils::createBoxVao()
{
        const float vertices[] = {
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

                -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
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

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return vao;
}

GLuint MeshUtils::createQuadVao()
{
        const GLfloat vertices[] = {
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
                (GLvoid*)0
        );
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(
                1,
                2,
                GL_FLOAT,
                GL_FALSE,
                5 * sizeof(GLfloat),
                (GLvoid*)(3 * sizeof(GLfloat))
        );
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        return vao;
}

void MeshUtils::drawQuad(Shader& shader, GLuint vao, glm::mat4& modelMatrix, glm::mat4& viewMatrix,
                         glm::mat4& projectionMatrix)
{
        shader.use();
        glBindVertexArray(vao);

        shader.setUniform("u_model", modelMatrix);
        shader.setUniform("u_view", viewMatrix);
        shader.setUniform("u_projection", projectionMatrix);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(0);
}

void MeshUtils::drawBox(Shader& shader, GLuint vao, glm::mat4& modelMatrix, glm::mat4& viewMatrix,
                        glm::mat4& projectionMatrix)
{
        shader.use();
        glBindVertexArray(vao);

        shader.setUniform("u_model", modelMatrix);
        shader.setUniform("u_view", viewMatrix);
        shader.setUniform("u_projection", projectionMatrix);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);
}
