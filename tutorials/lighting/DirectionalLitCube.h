//
// Created by Patrik Aradi on 2023/12/20.
//

#ifndef DIRECTIONALLITCUBE_H
#define DIRECTIONALLITCUBE_H

#include "../../engine/Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../engine/Camera.h"

#include "LightmapCube.h"

struct Material;

class LightCube;


class DirectionLitCube final : public LightmapCube
{
public:
    DirectionLitCube(const LightCube& light, const Engine::Camera& camera,
                                       const Engine::Texture& diffuseMap, const Engine::Texture& specularMap,
                                       const glm::vec3& lightDirection):
        lightDirection(lightDirection),
        LightmapCube(light, camera, diffuseMap, specularMap)
    {
        shader = Engine::Shader("shaders/tutorial_lighting/direction_lit_cube/vertex.glsl",
                                "shaders/tutorial_lighting/direction_lit_cube/fragment.glsl");
    }


    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    void setLightDirection(const glm::vec3& newLightDirection);

    ~DirectionLitCube() override = default;
private:
    glm::vec3 lightDirection{};
};


#endif //DIRECTIONALLITCUBE_H
