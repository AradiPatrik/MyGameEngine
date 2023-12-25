#ifndef MATERIALS_H
#define MATERIALS_H
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

namespace Engine
{
    class Shader;
}

struct Material
{
    constexpr Material(
        const glm::vec3 ambient,
        const glm::vec3 diffuse,
        const glm::vec3 specular,
        const float shininess
    ): ambient(ambient), diffuse(diffuse), specular(specular),
       shininess(shininess)
    {
    }

    void bindToShader(const Engine::Shader& shader) const;

    const glm::vec3 ambient;
    const glm::vec3 diffuse;
    const glm::vec3 specular;
    const float shininess;
};

const Material emerald(
    glm::vec3(0.0215, 0.1745, 0.0215),
    glm::vec3(0.07568, 0.61424, 0.07568),
    glm::vec3(0.633, 0.727811, 0.633),
    0.6
);



#endif //MATERIALS_H
