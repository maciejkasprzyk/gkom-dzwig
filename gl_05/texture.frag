#version 330 core

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;
in vec4 FragPosLightSpace;


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
uniform sampler2D shadowMap;
uniform vec3 lightPos;

out vec4 color;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

void main()
{
    // ambient light
    float ambientStrength = 0.5;

    // diffuse light
    float diffStrenght = max(dot(Normal, normalize(lightDir)), 0.0) * 0.7;
    float diffStrenght2 = max(dot(Normal, normalize(lightDir2)), 0.0) * 0.35;
    float diffStrenght3 = max(dot(Normal, normalize(lightDir3)), 0.0) * 0.10;
    float diffStrenght4 = max(dot(Normal, normalize(lightDir4)), 0.0) * 0.05;

    float shadow = ShadowCalculation(FragPosLightSpace);    


    vec3 lightStrenght = (-shadow + ambientStrength + diffStrenght + diffStrenght2 + diffStrenght3 + diffStrenght4) * lightColor;
    color = texture(Texture, TexCoord) * vec4(lightStrenght,1.0);
}
