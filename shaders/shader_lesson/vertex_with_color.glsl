#version 330 core
layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec3 inVertexColor;
out vec4 vertexColor;

uniform vec4 ourColor;

void main() {

    gl_Position = vec4(inVertexPosition, 1.0);
    vertexColor = vec4(inVertexColor, 1.0);
}
