#pragma once

#include "WorldEngine.h"

#include <SDL.h>
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace WorldEngine
{
	class Light
	{
	public:
		Light();
		Light(glm::vec3 color, GLfloat ambientIntensity, GLfloat diffuseIntensity);
		~Light();
		void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation);
	private:
		glm::vec3 color;
		GLfloat ambientIntensity;
		GLfloat diffuseIntensity;
	};
}