#version 450

in vec4 color;
in vec2 texCoord0;

out vec4 outColor;

struct DirectionalLight
{
	vec3 color;
	float ambientIntensity;
};

uniform sampler2D tex;
uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;
	outColor = texture(tex, texCoord0) * ambientColor;
}