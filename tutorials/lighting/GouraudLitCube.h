//
// Created by Patrik Aradi on 2023/12/9.
//

#ifndef GOURAUDLITCUBE_H
#define GOURAUDLITCUBE_H
#include "LitCube.h"


class GouraudLitCube : public LitCube
{
public:
    GouraudLitCube(const glm::vec3& cubeColor, const glm::vec3& lightColor, const LightCube& light,
                   const Engine::Camera& camera)
        : LitCube(cubeColor, lightColor, light, camera)
    {
        shader = Engine::Shader(
            "shaders/tutorial_lighting/gouraud_object/vertex.glsl",
            "shaders/tutorial_lighting/gouraud_object/fragment.glsl"
        );
    }
};


#endif //GOURAUDLITCUBE_H
