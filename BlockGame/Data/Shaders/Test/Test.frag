#version 460 core

out vec4 FragColor;

in vec2 textCoord;

uniform sampler2D givenTexture;

void main()
{
   FragColor = texture(givenTexture, textCoord);
}