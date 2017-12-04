#ifndef _GL_H_
#define _GL_H_

// Frameworks
#include <GL\glew.h>
#include <GLFW\glfw3.h>

// Maths
#include <GLM\glm.hpp>
#include <GLM\mat4x4.hpp>

// Transforms
#define GLM_ENABLE_EXPERIMENTAL
#include <GLM\gtx\transform.hpp>

#include <stdio.h>

static const struct Vertex
{
	float x, y;
	float r, g, b;
};

class GL
{
public:
	GLuint vBuffer, program;
	GL();
	int Initialize();

	static void ErrorCallback(int error, const char* description)
	{
		fprintf(stderr, "Error: %s\n", description);
	}
};

#endif
