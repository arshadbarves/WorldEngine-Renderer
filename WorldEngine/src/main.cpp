#define _CRT_SECURE_NO_WARNINGS

#include "WorldEngine.h"

#include <SDL.h>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"
//#include "Transform.h"
//#include "Material.h"
//#include "Model.h"
//#include "Skybox.h"
//#include "Terrain.h"
//#include "TerrainGenerator.h"
//#include "TerrainShader.h"
//#include "TerrainTexture.h"
//#include "TerrainTexturePack.h"
//#include "Water.h"
//#include "WaterShader.h"
//#include "WaterFrameBuffers.h"
//#include "GuiRenderer.h"
//#include "GuiTexture.h"
//#include "GuiShader.h"
//#include "Particle.h"
//#include "ParticleShader.h"
//#include "ParticleTexture.h"
//#include "ParticleRenderer.h"
//#include "ParticleMaster.h"
//#include "Fbo.h"
//#include "PostProcessing.h"
//#include "PostProcessingShader.h"
//#include "PostProcessingRenderer.h"
//#include "PostProcessingFrameBuffers.h"
//#include "ShadowMap.h"
//#include "ShadowShader.h"
//#include "ShadowRenderer.h"
//#include "ShadowFrameBuffers.h"
//#include "Entity.h"
//#include "EntityRenderer.h"
//#include "EntityShader.h"
//#include "EntityFrameBuffers.h"
//#include "EntityMaster.h"
//#include "EntityTexture.h"
//#include "EntityShader.h"
//#include "EntityRenderer.h"
//#include "EntityFrameBuffers.h"
//#include "EntityMaster.h"



namespace WorldEngine {

	// Constant Variables
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const char* WINDOW_TITLE = "World Engine";

	// Glabal Variables
	Window mainWindow;
	std::vector<Mesh*> meshList;
	std::vector<Shader*> shaderList;
	Camera camera;

	// Texture
	Texture brickTexture;
	Texture dirtTexture;

	// Light
	Light mainLight;

	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;

	glm::mat4 projection;
	glm::mat4 model;
	glm::mat4 view;


	GLuint UniformProjection, UniformModel = 0, UniformView = 0, UniformAmbientColor = 0, UniformAmbientIntensity = 0;

	static const char* vShader = "Shaders/VertexShader.glsl";
	static const char* fShader = "Shaders/FragmentShader.glsl";

	// Get OpenGL Version Information
	void GetOpenGLVersionInfo() {
		// Get OpenGL Version Information
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	}

	// Create Triangle
	void CreateObject() {
		// Create Triangle
		GLfloat vertices[] = {
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.5f, 1.0f
		};
		unsigned int indices[] = {
			0, 3, 1,
			1, 3, 2,
			2, 3, 0,
			0, 1, 2
		};
		Mesh* triangle = new Mesh();
		triangle->CreateMesh(vertices, indices, 20, 12);
		meshList.push_back(triangle);
	}

	// Create Shader
	void CreateShader() {
		// Create Shader
		Shader* shader = new Shader();
		shader->CreateFromFiles(vShader, fShader);
		shaderList.push_back(shader);
	}

	// Initialize
	void Intialization()
	{
		// Initialize Main Window
		mainWindow = Window();
		mainWindow.Initialize(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

		// Get OpenGL Version Information
		GetOpenGLVersionInfo();

		// Create Triangle
		CreateObject();

		// Create Shader
		CreateShader();

		projection = glm::perspective(glm::radians(45.0f), mainWindow.GetBufferWidth() / mainWindow.GetBufferHeight(), 0.1f, 100.0f);

		camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			-90.0f,
			0.0f,
			0.01f,
			0.05f);
	}

	// Handle Window Events
	void HandleWindowEvents(SDL_Event& e)
	{
		// Window Event
		if (e.type == SDL_WINDOWEVENT)
		{
			switch (e.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				// Update OpenGL Viewport
				glViewport(0, 0, e.window.data1, e.window.data2);
				// Update Projection Matrix
				projection = glm::perspective(glm::radians(45.0f), (float)e.window.data1 / (float)e.window.data2, 0.1f, 100.0f);
				break;
			}
		}
	}

	// Main Loop
	void MainLoop()
	{

		brickTexture = Texture();
		brickTexture.LoadTexture("Resources/Textures/brick.png");

		mainLight = Light(glm::vec3(1.0f, 1.0f, 1.0f),
			0.4f, 0.7f);

		// While application is running
		while (!mainWindow.GetShouldClose())
		{
			// Calculate Delta Time
			GLfloat now = SDL_GetTicks();
			deltaTime = now - lastTime;
			lastTime = now;

			// Handle events on queue
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0)
			{
				// User requests quit
				if (e.type == SDL_QUIT)
				{
					mainWindow.SetShouldClose(true);
				}
				// Handle Window Events
				HandleWindowEvents(e);
			}

			camera.KeyControl(mainWindow.GetKeys(), deltaTime);

			camera.MouseControl(mainWindow.GetXChange(), mainWindow.GetYChange());



			// Clear Color Buffer
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			// Clear Depth Buffer
			glClearDepth(1.0f);

			// Clear Color and Depth Buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Shader
			for (size_t i = 0; i < shaderList.size(); i++)
			{
				shaderList[i]->UseShader();
				shaderList[i]->DebugShader();
				UniformProjection = shaderList[i]->GetProjectionLocation();
				UniformModel = shaderList[i]->GetModelLocation();
				UniformView = shaderList[i]->GetViewLocation();
				UniformAmbientColor = shaderList[i]->GetAmbientColorLocation();
				UniformAmbientIntensity = shaderList[i]->GetAmbientIntensityLocation();
			}

			mainLight.UseLight(UniformAmbientIntensity, UniformAmbientColor);

			// Update Uniforms
			glUniformMatrix4fv(UniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			glUniformMatrix4fv(UniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(UniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));

			brickTexture.UseTexture();

			// Model
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
			model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

			// Draw Mesh
			for (size_t i = 0; i < meshList.size(); i++) {
				meshList[i]->RenderMesh();
			}

			glUseProgram(0);

			// Swap Window
			mainWindow.SwapBuffers();
		}
	}

	// Close
	void Close()
	{
		// Destroy Window
		mainWindow.Destroy();
		// Destroy Mesh
		for (size_t i = 0; i < meshList.size(); i++)
		{
			meshList[i]->ClearMesh();
		}
		// Destroy Shader
		for (size_t i = 0; i < shaderList.size(); i++)
		{
			shaderList[i]->ClearShader();
		}
	}

	// SDL main
	int SDL_main(int argc, char* args[])
	{
		// Initialize
		Intialization();

		// main loop
		MainLoop();

		// close
		Close();

		return 0;
	}
}

int main(int argc, char* args[])
{
	return WorldEngine::SDL_main(argc, args);
}