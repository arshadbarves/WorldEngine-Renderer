#include "Window.h"

namespace WorldEngine
{
	Window::Window()
	{
		window = NULL;
		glContext = NULL;
		quit = false;
		bufferWidth = 0;
		bufferHeight = 0;
		lastX = 0.0f;
		lastY = 0.0f;
		xChange = 0.0f;
		yChange = 0.0f;
		mouseFirstMoved = true;

		// Initialize keys
		for (size_t i = 0; i < 1024; i++)
		{
			keys[i] = false;
		}
	}

	Window::~Window()
	{
		Destroy();
	}

	int Window::Initialize(const char* title, int width, int height)
	{
		// Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			std::cerr << "SDL failed to initialize: " << SDL_GetError() << std::endl;
			return 1;
		}
		// Set OpenGL version to 4.5
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		// Set OpenGL profile to core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		// Set OpenGL context flags to forward compatible
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
			SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
		// Create window
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_MAXIMIZED);
		if (window == NULL)
		{
			std::cerr << "SDL failed to create window: " << SDL_GetError() << std::endl;
			return 1;
		}

		// Get frame buffer size
		SDL_GL_GetDrawableSize(window, &bufferWidth, &bufferHeight);

		// Set window icon
		SDL_Surface* icon = SDL_LoadBMP("icon.bmp");
		SDL_SetWindowIcon(window, icon);
		SDL_FreeSurface(icon);

		// Create callbacks
		CreateCallbacks();

		// Set window data
		SDL_SetWindowData(window, "window", this);


		// Create OpenGL context
		glContext = SDL_GL_CreateContext(window);
		if (glContext == NULL)
		{
			std::cerr << "SDL failed to create OpenGL context: " << SDL_GetError() << std::endl;
			return 1;
		}
		// Initialize GLEW
		glewExperimental = GL_TRUE;

		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			std::cerr << "GLEW failed to initialize: " << glewGetErrorString(error) << std::endl;
			return 1;
		}
		// Enable double buffering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		// Enable depth testing
		glEnable(GL_DEPTH_TEST);
		// Enable back face culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		// Enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::Destroy()
	{
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void Window::SwapBuffers()
	{
		SDL_GL_SwapWindow(window);
	}

	// Callbacks
	void Window::CreateCallbacks()
	{
		SDL_SetWindowData(window, "window", this);
		SDL_AddEventWatch(Window::HandleEventWrapper, this);
	}

	int Window::HandleEventWrapper(void* userdata, SDL_Event* event)
	{
		Window* win = (Window*)userdata;
		return win->HandleEvent(event);
	}

	int Window::HandleEvent(SDL_Event* event)
	{
		switch (event->type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_WINDOWEVENT:
			switch (event->window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				bufferWidth = event->window.data1;
				bufferHeight = event->window.data2;
				glViewport(0, 0, bufferWidth, bufferHeight);
				break;
			}
			break;
		case SDL_KEYDOWN:
			HandleKeyboardEvent(event, window, event->key.keysym.sym, event->key.keysym.scancode, event->key.state, event->key.keysym.mod);
			break;
		case SDL_KEYUP:
			HandleKeyboardEvent(event, window, event->key.keysym.sym, event->key.keysym.scancode, event->key.state, event->key.keysym.mod);
			break;
		case SDL_MOUSEMOTION:
			HandleMouseEvent(event, window, event->motion.x, event->motion.y);
			break;
		}

		return 0;
	}

	void Window::HandleKeyboardEvent(SDL_Event* event, SDL_Window* window, int key, int scancode, int action, int mode)
	{
		Window* win = (Window*)SDL_GetWindowData(window, "window");
		
		if (win != nullptr) {
			if (key >= 0 && key < 1024) {
				win->keys[key] = (action != SDL_RELEASED);
			}
			else {
				// Handle out-of-bounds key index error
				// You may throw an exception, log an error, or take any appropriate action
				printf("Key index %d is out of bounds\n", key);
			}
		}
		else {
			// Handle invalid window or uninitialized win pointer
			// You may throw an exception, log an error, or take any appropriate action
			printf("Invalid window or uninitialized window pointer\n");
		}
	}

	void Window::HandleMouseEvent(SDL_Event* event, SDL_Window* window, double xpos, double ypos)
	{
		Window* win = (Window*)SDL_GetWindowData(window, "window");

		if (win->mouseFirstMoved)
		{
			win->lastX = xpos;
			win->lastY = ypos;
			win->mouseFirstMoved = false;
		}

		win->xChange = xpos - win->lastX; // Inverted since x-coordinates range from left to right
		win->yChange = win->lastY - ypos; // Inverted since y-coordinates range from bottom to top

		win->lastX = xpos;
		win->lastY = ypos;
	}

	GLfloat Window::GetXChange()
	{
		GLfloat change = xChange;
		xChange = 0.0f; // Rework this later to avoid resetting every frame (maybe use a bool)
		return change;
	}

	GLfloat Window::GetYChange()
	{
		GLfloat change = yChange;
		yChange = 0.0f; // Rework this later to avoid resetting every frame (maybe use a bool)
		return change;
	}
}