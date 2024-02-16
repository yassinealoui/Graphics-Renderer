#shader Vertex
#version 330 core 

layout (location = 0) in vec4 position;
void main()
{
	gl_Position = position;
};

#shader Fragment
#version 330 core

void main()
{
	gl_FragColor = vec4(0.5f ,0.6f ,0.8f ,1f);
};
