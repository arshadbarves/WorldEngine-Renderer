#pragma once

#include "WorldEngine.h"

#include <GL/glew.h>

namespace WorldEngine
{
	class Shader
	{
	public:
		Shader();
		~Shader();
		void CreateFromString(const char* vertexCode, const char* fragmentCode);
		void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
		GLuint GetProjectionLocation();
		GLuint GetModelLocation();
		GLuint GetViewLocation();
		GLuint GetAmbientIntensityLocation();
		GLuint GetAmbientColorLocation();
		GLuint GetDiffuseIntensityLocation();
		GLuint GetDirectionLocation();
		GLuint GetSpecularIntensityLocation();
		GLuint GetShininessLocation();
		GLuint GetEyePositionLocation();
		void UseShader();
		void ClearShader();
		void DebugShader();
	private:
		GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDirection, uniformSpecularIntensity, uniformShininess, uniformEyePosition;
		std::string ReadFile(const char* fileLocation);
		void CompileShader(const char* vertexCode, const char* fragmentCode);
		void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	};
};
