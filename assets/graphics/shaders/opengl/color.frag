#version 410

uniform vec4 tint = vec4(1.0,1.0,1.0,1.0);
in vec2 texCoord;
in mat4 modelViewProjection;

out vec4 COLOR;

void main() {
    COLOR = tint;
}