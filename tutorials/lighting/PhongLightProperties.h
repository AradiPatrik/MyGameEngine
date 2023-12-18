//
// Created by Patrik Aradi on 2023/12/18.
//

#ifndef PHONGLIGHTPROPERTIES_H
#define PHONGLIGHTPROPERTIES_H
#include <glm/glm.hpp>

class PhongLightProperties {
public:
    PhongLightProperties(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

    const glm::vec3 ambient;
    const glm::vec3 diffuse;
    const glm::vec3 specular;
};



#endif //PHONGLIGHTPROPERTIES_H
