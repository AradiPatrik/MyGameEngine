//
// Created by Taipei Home on 12/23/2023.
//

#ifndef DIRECTINOALLIGHT_H
#define DIRECTINOALLIGHT_H
#include "glm/vec3.hpp"

namespace Engine {
class Shader;
}
class DirectinoalLight {
public:
    DirectinoalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
    void bindToShader(const Engine::Shader& shader) const;

private:
    glm::vec3 m_direction;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
};

#endif // DIRECTINOALLIGHT_H
