#shader Vertex
#version 330 core 

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 u_MVP;
uniform mat4 u_Rotation;
void main()
{
	gl_Position = u_Rotation * u_MVP * position;
	v_TexCoord = texCoord;
};


#shader Fragment
#version 330 core

uniform vec4 u_color;
in vec2 v_TexCoord;
//uniform sampler2D u_Texture;

void main()
{
	//vec4 textureColor = texture(u_Texture, v_TexCoord);

	float distance = sqrt(dot(v_TexCoord - vec2(0.5), v_TexCoord - vec2(0.5)));
	vec4 color = vec4(0, 0, 0 , 1);
	color.rgb = vec3(1 - smoothstep(0.49 , 0.5, distance));
	gl_FragColor = color;
};