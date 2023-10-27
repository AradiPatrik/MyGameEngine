//
// Created by Patrik Aradi on 2023/10/26.
//

#ifndef OPENGL_PLAYGROUND_SHADER_H
#define OPENGL_PLAYGROUND_SHADER_H

#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <OpenGL/gl3.h>
#include <fstream>
#include <glm/glm.hpp>

namespace Engine {

    class Shader {
    private:
        GLuint programId;

        static GLuint compileShader(const std::string &path, GLenum type);

        static GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader);

    public:
        Shader(const std::string &vertexPath, const std::string &fragmentPath);

        void use() const;

        void setUniform(const std::string &name, GLboolean value) const;

        void setUniform(const std::string &name, GLint value) const;

        void setUniform(const std::string &name, GLfloat value) const;

        void setUniform(const std::string &name, const glm::mat4 &value) const;

        void setUniform(const std::string &name, const glm::vec3 &value) const;

        void setUniform(const std::string &name, const glm::vec4 &value) const;
    };

} // Engine

#endif //OPENGL_PLAYGROUND_SHADER_H
