#shader Vertex
#version 330 core 

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;

out vec2 v_texCoord;

void main()
{
	gl_Position = position;
	v_texCoord = texCoord;
};


#shader Fragment
#version 330 core

uniform vec4 u_color;
in vec2 v_texCoord;
uniform sampler2D u_Texture;

void main()
{
	vec4 textureColor = texture(u_Texture, v_texCoord);
	gl_FragColor = textureColor;
};
