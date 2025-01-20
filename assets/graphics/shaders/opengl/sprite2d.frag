#version 410

uniform bool useTexture = false;
uniform sampler2D spriteTexture;

uniform bool useNormalMap = false;
uniform sampler2D normalMap;
uniform float normalStrength = 1.0;

uniform vec4 tint = vec4(1.0,1.0,1.0,1.0);
in vec2 texCoord;
in mat4 modelViewProjection;

out vec4 COLOR;

void main() {
    if(useTexture == true)
    {
        COLOR = texture(spriteTexture, texCoord) * tint;
    }
    else
    {
        COLOR = tint;
    }

    vec2 sun = -vec2(0.5,0.5);
    //Rotate the sun based on the matrix
    sun = (modelViewProjection * vec4(sun,0.0, 1.0)).xy;


    if(useNormalMap == true)
    {
        vec3 normal = mix(vec3(0.0,0.0,1.0), normalize(texture(normalMap, texCoord).xyz * 2.0 - 1.0), normalStrength);
        vec3 lightDir = normalize(vec3(sun, 0.0));
        float diff = max(dot(normal, lightDir), 0.0) + 0.25;
        COLOR.rgb *= diff;
    }

    //COLOR = vec4(texCoord.x,texCoord.y,0.0,1.0);
}