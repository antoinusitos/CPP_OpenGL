#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 myModel;
uniform mat4 myView;
uniform mat4 myProjection;

void main()
{
    gl_Position = myProjection * myView * myModel * vec4(aPos, 1.0);
} 