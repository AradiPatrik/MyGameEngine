#include "Materials.h"

#include "Shader.h"

void Material::bindToShader(const Engine::Shader& shader) const
{
    shader.setUniform("u_material.ambient", ambient);
    shader.setUniform("u_material.diffuse", diffuse);
    shader.setUniform("u_material.specular", specular);
    shader.setUniform("u_material.shininess", shininess);
}
