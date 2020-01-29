#version 330 core

in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D Texture;
uniform vec3 lightDir = vec3(0.8,-2.0,0.4);
uniform vec3 lightDir2 = vec3(-0.4,-2.0,0.8);
uniform vec3 lightColor = vec3(1.0,1.0,1.0);

out vec4 color;

void main()
{
    // ambient light
    float ambientStrength = 0.5;

    // diffuse light
    float diffStrenght = max(dot(Normal, normalize(lightDir)), 0.0) * 0.5;
    float diffStrenght2 = max(dot(Normal, normalize(lightDir2)), 0.0) * 0.5;

    vec3 lightStrenght = (ambientStrength + diffStrenght + diffStrenght2) * lightColor;
    color = texture(Texture, TexCoord) * vec4(lightStrenght,1.0);
}
