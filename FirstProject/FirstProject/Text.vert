#version 330 core
layout (location = 0) in vec4 myVertex; // <vec2 pos, vec2 tex>
out vec2 myTexCoords;

uniform mat4 myProjection;

void main()
{
    gl_Position = myProjection * vec4(myVertex.xy, 0.0, 1.0);
    myTexCoords = myVertex.zw;
} 