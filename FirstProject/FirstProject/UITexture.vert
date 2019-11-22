#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 myModel;
uniform mat4 myProjection;

void main()
{
	TexCoords = vertex.zw;
    gl_Position = myProjection * myModel * vec4(vertex.xy, 0.0f, 1.0);
} 