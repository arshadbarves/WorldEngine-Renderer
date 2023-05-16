#include "Shader.h"

namespace WorldEngine
{
	Shader::Shader()
	{
		// Initialize Shader
		shaderID = 0;
		uniformModel = 0;
		uniformProjection = 0;
	}
	Shader::~Shader()
	{
		// Delete Shader
		ClearShader();
	}
	void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
	{
		CompileShader(vertexCode, fragmentCode);
	}
	void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
	{
		std::string vertexString = ReadFile(vertexLocation);
		std::string fragmentString = ReadFile(fragmentLocation);
		const char* vertexCode = vertexString.c_str();
		const char* fragmentCode = fragmentString.c_str();
		CompileShader(vertexCode, fragmentCode);
	}
	std::string Shader::ReadFile(const char* fileLocation)
	{
		std::string content;
		std::ifstream fileStream(fileLocation, std::ios::in);
		if (!fileStream.is_open())
		{
			printf("Failed to read %s! File doesn't exist.", fileLocation);
			return "";
		}
		std::string line = "";
		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			content.append(line + "\n");
		}
		fileStream.close();
		return content;
	}
	GLuint Shader::GetProjectionLocation()
	{
		return uniformProjection;
	}
	GLuint Shader::GetModelLocation()
	{
		return uniformModel;
	}
	GLuint Shader::GetViewLocation()
	{
		return uniformView;
	}
	GLuint Shader::GetAmbientIntensityLocation()
	{
		return uniformAmbientIntensity;
	}
	GLuint Shader::GetAmbientColorLocation()
	{
		return uniformAmbientColor;
	}
	void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
	{
		// Create Shader Program
		shaderID = glCreateProgram();
		if (!shaderID)
		{
			printf("Error creating shader program!\n");
			return;
		}
		// Create Vertex Shader
		AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
		// Create Fragment Shader
		AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);
		// Create Status
		GLint result = 0;
		GLchar eLog[1024] = { 0 };
		// Link Shader Program
		glLinkProgram(shaderID);
		glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
			printf("Error linking program: '%s'\n", eLog);
			return;
		}
		// Validate Shader Program
		glValidateProgram(shaderID);
		glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
			printf("Error validating program: '%s'\n", eLog);
			return;
		}
		// Get Uniforms
		uniformModel = glGetUniformLocation(shaderID, "model");
		uniformProjection = glGetUniformLocation(shaderID, "projection");
		uniformView = glGetUniformLocation(shaderID, "view");
		uniformAmbientColor = glGetUniformLocation(shaderID, "directionalLight.color");
		uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");
	}
	void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
	{
		// Create Shader
		GLuint theShader = glCreateShader(shaderType);
		// Create Status
		GLint result = 0;
		GLchar eLog[1024] = { 0 };
		// Compile Shader
		glShaderSource(theShader, 1, &shaderCode, NULL);
		glCompileShader(theShader);
		glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
		if (result != GL_TRUE)
		{
			glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
			printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
			return;
		}
		// Attach Shader
		glAttachShader(theProgram, theShader);
	}

	void Shader::UseShader()
	{
		glUseProgram(shaderID);
	}
	void Shader::ClearShader()
	{
		if (shaderID != 0)
		{
			glDeleteProgram(shaderID);
			shaderID = 0;
		}
		uniformModel = 0;
		uniformProjection = 0;
	}
	void Shader::DebugShader()
	{
		printf("Shader ID: %d\n", shaderID);
		printf("Uniform Model: %d\n", uniformModel);
		printf("Uniform Projection: %d\n", uniformProjection);
		printf("Uniform View: %d\n", uniformView);
		printf("Uniform Ambient Color: %d\n", uniformAmbientColor);
		printf("Uniform Ambient Intensity: %d\n", uniformAmbientIntensity);
	}
}
