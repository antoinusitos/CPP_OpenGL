#version 330 core
in vec2 TexCoords;
out vec4 myFragColor;

uniform sampler2D myImage;
uniform vec3 mySpriteColor;

void main()
{
    myFragColor = vec4(mySpriteColor, 1.0) * texture(myImage, TexCoords);
}