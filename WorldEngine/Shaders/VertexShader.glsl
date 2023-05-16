#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec4 color;
out vec2 texCoord0;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;


void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	color = vec4(clamp(position, 0.0f, 1.0f), 1.0f);

	texCoord0 = texCoord;
}
