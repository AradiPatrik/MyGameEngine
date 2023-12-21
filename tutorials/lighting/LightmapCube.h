//
// Created by Patrik Aradi on 2023/12/18.
//

#ifndef LIGHTMAPCUBE_H
#define LIGHTMAPCUBE_H

#include "../../engine/Texture.h"
#include "../../engine/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


struct Material;

namespace Engine
{
    class Camera;
}

class LightCube;


class LightmapCube
{
public:
    virtual ~LightmapCube() = default;
    LightmapCube(
        const LightCube& light,
        const Engine::Camera& camera,
        const Engine::Texture& diffuseMap,
        const Engine::Texture& specularMap
    );
    virtual void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void setPosition(const glm::vec3& newPosition);
    void setRotation(const glm::vec3& newRotation);

protected:
    GLuint vao;

    Engine::Shader shader;
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    const LightCube& light;
    const Engine::Camera& camera;
    const Engine::Texture diffuseMap;
    const Engine::Texture specularMap;
};


#endif //LIGHTMAPCUBE_H
