//
// Created by Patrik Aradi on 2023/10/26.
//

#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

namespace Engine {
    Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
        GLuint vertexShader = compileShader(vertexPath, GL_VERTEX_SHADER);
        GLuint fragmentShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);

        programId = linkProgram(vertexShader, fragmentShader);
    }

    GLuint Shader::compileShader(const std::string &path, GLenum type) {
        std::ifstream shaderFile(path.c_str());
        if (!shaderFile.is_open()) {
            std::cerr << "Failed to open vertex shader file" << std::endl;
            throw std::runtime_error("Failed to open vertex shader file");
        }

        std::string shaderSource(
                (std::istreambuf_iterator<char>(shaderFile)),
                std::istreambuf_iterator<char>()
        );

        const char *shaderSourceCStr = shaderSource.c_str();
        const GLuint vertexShader = glCreateShader(type);
        glShaderSource(vertexShader, 1, &shaderSourceCStr, nullptr);
        glCompileShader(vertexShader);

        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            std::cerr << "Failed to compile vertex shader" << std::endl;
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cerr << infoLog << std::endl;
            throw std::runtime_error("Failed to compile vertex shader");
        }

        return vertexShader;
    }

    GLuint Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);

        glLinkProgram(shaderProgram);

        GLint success;
        GLchar infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            std::cerr << "Failed to link shader program" << std::endl;
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::cerr << infoLog << std::endl;
            throw std::runtime_error("Failed to link shader program");
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }

    void Shader::use() const {
        glUseProgram(programId);
    }

    void Shader::setUniform(const std::string &name, const GLboolean value) const {
        glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
    }

    void Shader::setUniform(const std::string &name, const GLint value) const {
        glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
    }

    void Shader::setUniform(const std::string &name, const GLfloat value) const {
        glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
    }

    void Shader::setUniform(const std::string &name, const glm::mat4 &value) const {
        glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::setUniform(const std::string &name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(programId, name.c_str()), 1, glm::value_ptr(value));
    }

    void Shader::setUniform(const std::string &name, const glm::vec4 &value) const {
        glUniform4fv(glGetUniformLocation(programId, name.c_str()), 1, glm::value_ptr(value));
    }
} // Engine