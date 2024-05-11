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
uniform float u_TintIntensity = 1.0;
in vec2 v_TexCoord;
uniform sampler2D u_Texture;

void main()
{
	vec4 textureColor = texture(u_Texture, v_TexCoord);
	gl_FragColor = mix(textureColor, textureColor * u_color, u_TintIntensity);
};
