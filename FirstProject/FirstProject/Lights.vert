#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3					myFragPos;
out vec3					myNormal;
out vec2					myTexCoords;

uniform mat4				myModel;
uniform mat4				myView;
uniform mat4				myProjection;

void main()
{
    myFragPos = vec3(myModel * vec4(aPos, 1.0));
    myNormal = mat3(transpose(inverse(myModel))) * aNormal;  
    myTexCoords = aTexCoords;
    
    gl_Position = myProjection * myView * vec4(myFragPos, 1.0);
}