//
// Created by Patrik Aradi on 2023/12/18.
//

#include "PhongLightProperties.h"

PhongLightProperties::PhongLightProperties(
    const glm::vec3& ambient,
    const glm::vec3& diffuse,
    const glm::vec3& specular
): ambient(ambient),
   diffuse(diffuse),
   specular(specular)
{
}
