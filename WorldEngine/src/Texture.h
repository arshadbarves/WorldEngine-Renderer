#pragma once

#include "WorldEngine.h"

#include <GL/glew.h>
#include <SDL_image.h>

namespace WorldEngine
{
	class Texture
	{
	public:
		Texture();
		~Texture();
		void LoadTexture(const char* fileLocation);
		void UseTexture();
		void ClearTexture();
	private:
		GLuint textureID;
		int width, height, bitDepth;
	};
}

