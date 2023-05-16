#include "Texture.h"

// Load texture from file using SDL_image
namespace WorldEngine
{
	Texture::Texture()
	{
		textureID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
	}
	Texture::~Texture()
	{
		ClearTexture();
	}
    void Texture::LoadTexture(const char* fileLocation)
    {
        // Load texture data from file
        SDL_Surface* imageSurface = IMG_Load(fileLocation);
        if (!imageSurface) {
            printf("Failed to load image: %s\n", IMG_GetError());
            IMG_Quit();
            // Throw an exception or return an error code here if appropriate
            return;
        }

        // Get texture width, height, and bit depth
        width = imageSurface->w;
        height = imageSurface->h;
        bitDepth = imageSurface->format->BitsPerPixel;


        // Set OpenGL pixel format based on loaded image
        GLenum format = GL_RGBA;
        if (bitDepth == 24) {
			format = GL_RGB;
		}
        else if (bitDepth == 32) {
            format = GL_RGBA;
        }
        else {
			printf("Unrecognized image format: %d bits per pixel\n", bitDepth);
			SDL_FreeSurface(imageSurface);
			// Throw an exception or return an error code here if appropriate
			return;
		}

        // print texture info
        printf("Loaded texture: %s\n", fileLocation);
        printf("Texture width: %d\n", width);
        printf("Texture height: %d\n", height);
        printf("Texture bit depth: %d\n", bitDepth);
        printf("Texture format: %d\n", format);

        // Generate texture
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // Set texture wrapping on the x-axis
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  // Set texture wrapping on the y-axis
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // Set minification filter
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // Set magnification filter

        // Load texture data
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageSurface->pixels);

        // Check for OpenGL errors
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            printf("Failed to create texture. OpenGL error: %d\n", error);
            glDeleteTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, 0);
            SDL_FreeSurface(imageSurface);
            // Throw an exception or return an error code here if appropriate
            return;
        }

        // Generate mipmaps
        glGenerateMipmap(GL_TEXTURE_2D);

        // Unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // Free texture data
        SDL_FreeSurface(imageSurface);
    }

	void Texture::UseTexture()
	{
		// Bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
	void Texture::ClearTexture()
	{
		// Delete texture
		glDeleteTextures(1, &textureID);
		textureID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
	}
}
