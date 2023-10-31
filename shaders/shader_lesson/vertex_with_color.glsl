#version 330 core
layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec3 inVertexColor;
out vec4 vertexColor;
out vec4 vertexPosition;

uniform float horizontalOffset;

void main() {
    gl_Position = vec4(inVertexPosition.x + horizontalOffset, -inVertexPosition.y, inVertexPosition.z, 1.0);
    vertexPosition = vec4(inVertexPosition.x + horizontalOffset, -inVertexPosition.y, inVertexPosition.z, 1.0);
    vertexColor = vec4(inVertexColor, 1.0);
}
