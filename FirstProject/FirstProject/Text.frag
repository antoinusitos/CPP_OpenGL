#version 330 core
in vec2 myTexCoords;
out vec4 myColor;

uniform sampler2D myText;
uniform vec3 myTextColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(myText, myTexCoords).r);
    myColor = vec4(myTextColor, 1.0) * sampled;
}  

