//
// Created by Patrik Aradi on 2023/10/29.
//

#ifndef OPENGL_PLAYGROUND_TEXTURE_H
#define OPENGL_PLAYGROUND_TEXTURE_H

#include <string>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <glad/glad.h>
#endif

namespace Engine {
class Shader;

class Texture {
    GLuint m_textureId;
    GLuint m_vao = 0;

public:
    explicit Texture(const std::string& path);

    void bind() const;
    void bind(GLenum position) const;
    void bind(const Shader& shader, GLenum position, const std::string& uniformName) const;


    void drawDebugQuad(const Shader& shader);
};
}

#endif // OPENGL_PLAYGROUND_TEXTURE_H
