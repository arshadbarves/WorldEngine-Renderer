#include "Light.h"

namespace WorldEngine
{
	Light::Light()
	{
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		ambientIntensity = 1.0f;
		diffuseIntensity = 0.0f;
	}
	Light::Light(glm::vec3 color, GLfloat ambientIntensity, GLfloat diffuseIntensity)
	{
		this->color = color;
		this->ambientIntensity = ambientIntensity;
		this->diffuseIntensity = diffuseIntensity;
	}
	Light::~Light()
	{
		// Nothing to do here
	}
	void Light::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation)
	{
		glUniform3f(ambientColorLocation, color.x, color.y, color.z);
		glUniform1f(ambientIntensityLocation, ambientIntensity);

		printf("Ambient Color: %f, %f, %f\n", color.x, color.y, color.z);
		printf("Ambient Intensity: %f\n", ambientIntensity);

		// Check for errors
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "Error setting light! " << error << std::endl;
		}
	}
}