#version 330 core

in vec2 v_uv;

out vec4 fragColor;

uniform vec4 u_borderColor;
uniform float u_borderSize;
uniform vec4 u_fillColor;

void main() {
    // checkered board
    if (mod(floor(v_uv.x * 10.0) + floor(v_uv.y * 10.0), 2.0) == 0.0) {
        fragColor = u_fillColor;
    } else {
        fragColor = u_borderColor;
    }

    //    if (v_uv.x < u_borderSize || v_uv.x > 1.0 - u_borderSize || v_uv.y < u_borderSize || v_uv.y > 1.0 - u_borderSize) {
    //        fragColor = u_borderColor;
    //    } else {
    //        fragColor = u_fillColor;
    //    }
}
