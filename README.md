# WorldEngine-Renderer

## World Engine

World Engine is an OpenGL-based rendering engine written in C++ that provides basic rendering features such as diffuse, ambient, spot, point lights, shadow maps, and more. It serves as a learning tool for understanding the fundamentals of OpenGL and can be used as a starting point for creating your own projects and games.

## Features

World Engine currently supports the following features:

- Diffuse and ambient lighting
- Spot and point lights
- Shadow mapping
- SDL (Simple DirectMedia Layer) for window management and input handling
- GLM (OpenGL Mathematics) for mathematics and vector operations
- GLEW (OpenGL Extension Wrangler Library) for managing OpenGL extensions
- Premake for build configuration

## Usage

To use World Engine, follow these steps:

Clone the repository:

`git clone https://github.com/arshadbarves/WorldEngine-Renderer.git`

Third Party Libraries:

- SDL: https://www.libsdl.org/download-2.0.php
- GLM: https://github.com/g-truc/glm
- GLEW: http://glew.sourceforge.net/

Build the project using Premake:

Navigate to the root directory of the project and run the following command:

`GenerateProjects.bat`

Click on GenerateProjects.bat to generate the project files for your preferred development environment. The project files will be generated in the build directory. For example, if you want to generate Visual Studio 2019 project files, run the following command:

`GenerateProjects.bat`

Open the generated project file in your preferred development environment.

Build and run the project.

Feel free to modify the code as you see fit and adapt it to your own needs. There are no specific licensing or usage rules associated with this project. You can use it for learning purposes or incorporate it into your own projects. The project will be updated periodically whenever time permits.

## Future Plans

In the future, World Engine will be expanded to include support for DirectX and Vulkan. Additional features such as global illumination and other advanced rendering techniques will also be implemented.

## Contributions

Contributions to World Engine are welcome. If you would like to contribute to the project, feel free to submit pull requests or open issues to discuss potential improvements or bug fixes.

Enjoy using World Engine and have fun exploring the world of OpenGL!
