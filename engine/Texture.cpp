//
// Created by Patrik Aradi on 2023/10/29.
//

#include "Texture.h"

#include "MeshUtils.h"

#include <stdexcept>

#include "Shader.h"
#include "stb_image.h"

namespace Engine {
Texture::Texture(const std::string& path)
{
    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data == nullptr) {
        throw std::runtime_error("Failed to load texture");
    }

    GLuint texture;
    glGenTextures(1, &texture);
    m_textureId = texture;
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        width,
        height,
        0,
        nrChannels == 3 ? GL_RGB : GL_RGBA,
        GL_UNSIGNED_BYTE,
        data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void Texture::bind() const
{
    bind(GL_TEXTURE0);
}

void Texture::bind(const GLenum position) const
{
    glActiveTexture(position);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}

void Texture::bind(const Shader& shader, GLenum position, const std::string& uniformName) const
{
    shader.use();
    shader.setUniform(uniformName, static_cast<GLint>(position - GL_TEXTURE0));
    bind(position);
}
void Texture::drawDebugQuad(const Shader& shader)
{
    if (m_vao == 0) {
        m_vao = MeshUtils::createTextureDebugQuadVao();
    }

    bind(shader, GL_TEXTURE0, "u_texture");
    MeshUtils::drawTextureDebugQuad(shader, m_vao);
}
}
