//
// Created by Patrik Aradi on 2023/12/18.
//

#include "LightmapCube.h"
#include "LightCube.h"
#include "../../engine/MeshUtils.h"
#include "../../engine/Camera.h"

struct Material;

LightmapCube::LightmapCube(
    const LightCube& light,
    const Camera& camera,
    const Texture& diffuseMap,
    const Texture& specularMap
): vao(MeshUtils::createBoxWithNormalsAndUvs()),
   shader(
       "shaders/tutorial_lighting/light_map_object/vertex.glsl",
       "shaders/tutorial_lighting/light_map_object/fragment.glsl"),
   position(0, 0, 0),
   light(light),
   camera(camera),
   diffuseMap(diffuseMap),
   specularMap(specularMap)
{
}

void LightmapCube::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    shader.use();
    auto modelMatrix = glm::mat4(1.0f);
    modelMatrix = translate(modelMatrix, position);
    light.bindToShader(shader);
    diffuseMap.bind(shader, GL_TEXTURE0, "u_material.diffuse");
    specularMap.bind(shader, GL_TEXTURE1, "u_material.specular");
    shader.setUniform("u_material.shininess", 32.0f);
    shader.setUniform("u_viewPosition", camera.getPosition());
    MeshUtils::drawBox(shader, vao, modelMatrix, viewMatrix, projectionMatrix);
}

void LightmapCube::setPosition(const glm::vec3& newPosition)
{
    position = newPosition;
}
