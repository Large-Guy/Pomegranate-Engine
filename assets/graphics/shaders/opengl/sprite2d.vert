#version 410

layout(location = 0) in vec2 VERTEX;
layout(location = 1) in vec2 VERTEX_TEXCOORD;
layout(location = 2) in vec3 VERTEX_COLOR;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int zIndex;

out vec2 texCoord;
out vec3 color;
out mat4 modelViewProjection;

void main() {
    gl_Position = projection * view * model * vec4(VERTEX,0.0, 1.0);
    gl_Position.z = float(zIndex) / 1000.0;
    texCoord = VERTEX_TEXCOORD;
    color = VERTEX_COLOR;
    modelViewProjection = projection * view * model;
}