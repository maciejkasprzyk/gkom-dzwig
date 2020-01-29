#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D Texture;


void main()
{
    // color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    color = texture(Texture, TexCoord);
}
