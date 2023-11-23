#version 330 core

in vec2 v_uv;

out vec4 fragColor;

uniform vec4 u_borderColor;
uniform float u_borderSize;
uniform vec4 u_fillColor;

void main() {
    if (v_uv.x < u_borderSize || v_uv.x > 1.0 - u_borderSize || v_uv.y < u_borderSize || v_uv.y > 1.0 - u_borderSize) {
        fragColor = u_borderColor;
    } else {
        fragColor = u_fillColor;
    }
}
