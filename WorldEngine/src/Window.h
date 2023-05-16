#pragma once

#include "WorldEngine.h"

#include <GL/glew.h>
#include <SDL.h>

namespace WorldEngine
{
	class Window {
	public:
		Window();
		~Window();
		int Initialize(const char* title, int width, int height);
		GLfloat GetBufferWidth() { return static_cast<GLfloat>(bufferWidth); }
		GLfloat GetBufferHeight() { return static_cast<GLfloat>(bufferHeight); }
		bool GetShouldClose() { return quit; }
		void SetShouldClose(bool value) { quit = value; }
		void SwapBuffers();
		void Destroy();

		bool* GetKeys() { return keys; }
		GLfloat GetXChange();
		GLfloat GetYChange();

	private:
		SDL_Window* window;
		SDL_GLContext glContext;
		bool quit;
		GLint bufferWidth;
		GLint bufferHeight;

		bool keys[1024];

		GLfloat lastX;
		GLfloat lastY;
		GLfloat xChange;
		GLfloat yChange;
		bool mouseFirstMoved; // Prevents camera from jumping to mouse position on first move event (when mouse is centered)

		void CreateCallbacks();
		int HandleEvent(SDL_Event* event);
		static int HandleEventWrapper(void* userdata, SDL_Event* event);
		static void HandleKeyboardEvent(SDL_Event* event, SDL_Window* window, int key, int scancode, int action, int mode);
		static void HandleMouseEvent(SDL_Event* event, SDL_Window* window, double xpos, double ypos);
	};
};


