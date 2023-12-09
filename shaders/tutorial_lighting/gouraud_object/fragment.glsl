#version 330 core
out vec4 fragmentColor;

in vec3 v_vertexColor;

void main()
{
    fragmentColor = vec4(v_vertexColor, 1.0);
}
