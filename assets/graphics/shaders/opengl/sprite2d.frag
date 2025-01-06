#version 410

uniform bool useTexture = false;
uniform sampler2D spriteTexture;
uniform vec4 tint = vec4(1.0,1.0,1.0,1.0);
in vec2 texCoord;

out vec4 COLOR;

void main() {
    if(useTexture)
    {
        COLOR = texture(spriteTexture, texCoord) * tint;
    }
    else
    {
        COLOR = tint;
    }
}