#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 myTexCoords;

uniform mat4 myModel;
uniform mat4 myView;
uniform mat4 myProjection;

void main()
{
    myTexCoords = aTexCoords;    
    gl_Position = myProjection * myView * myModel * vec4(aPos, 1.0);
}