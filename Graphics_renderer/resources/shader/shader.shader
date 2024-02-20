#shader Vertex
#version 330 core 

layout (location = 0) in vec4 position;
void main()
{
	gl_Position = position;
};

#shader Fragment
#version 330 core

uniform vec4 u_color;

void main()
{
	gl_FragColor = u_color;
};
