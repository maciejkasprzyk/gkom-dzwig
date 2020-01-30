#version 330 core

in vec3 Normal;
in vec2 TexCoord;

//najmocniejsze
uniform vec3 lightDir = vec3(-1.0,-1.0,0.0);
//boczne srednie
uniform vec3 lightDir2 = vec3(0.0,-1.0,-1.0);
//boczne slabe
uniform vec3 lightDir3 = vec3(0.0,-1.0,1.0);
//tylne bardzo slabe
uniform vec3 lightDir4 = vec3(1.0, 0.0,0.0);

uniform vec3 lightColor = vec3(1.0,1.0,1.0);

uniform sampler2D Texture;

out vec4 color;

void main()
{
    // ambient light
    float ambientStrength = 0.5;

    // diffuse light
    float diffStrenght = max(dot(Normal, normalize(lightDir)), 0.0) * 0.7;
    float diffStrenght2 = max(dot(Normal, normalize(lightDir2)), 0.0) * 0.35;
    float diffStrenght3 = max(dot(Normal, normalize(lightDir3)), 0.0) * 0.10;
    float diffStrenght4 = max(dot(Normal, normalize(lightDir4)), 0.0) * 0.05;

    vec3 lightStrenght = (ambientStrength + diffStrenght + diffStrenght2 + diffStrenght3 + diffStrenght4) * lightColor;
    color = texture(Texture, TexCoord) * vec4(lightStrenght,1.0);
}
