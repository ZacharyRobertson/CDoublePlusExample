#include "GL.h"
#include "Window.h"
#include "Shader.h"
#include "Triangle.h"
#include <iostream>

using namespace std;

int main()
{
	GL graphics;
	// Init Graphics
	if (graphics.Initialize() < 0)
	{
		cout << "Error: GL did not initialize due to error" << endl;
		system("pause");
		return -1;
	}

	// Create a window
	Window* window = new Window();
	window->CreateWindow(640, 480, "Hello World!", NULL, NULL);
	// Set window properties
	window->FocusWindow();
	window->EnableVSync();

	// Initialize Glew
	glewInit();

	// Create Shaders
	Shader vertShader = Shader("vert.glsl", ShaderType::VERTEX);
	Shader fragShader = Shader("frag.glsl", ShaderType::FRAGMENT);
	// Compile Shaders
	vertShader.Compile();
	fragShader.Compile();
	// Create Shader program
	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader.handle);
	glAttachShader(program, fragShader.handle);
	glLinkProgram(program);

	glUseProgram(program);
	//Create Shape
	Triangle triangle;
	triangle.Start();
	
	// Game Loop
	while (window->IsOpen())
	{
		// Begin Window
		window->RefreshViewport();

		// Clear the buffer
		glClear(GL_COLOR_BUFFER_BIT);
		// Update the shape
		triangle.Update();
		// Draw the shape
		triangle.Draw(program);

		// End Window
		window->End();
	}
	// Terminate GLFW
	return 0;
}