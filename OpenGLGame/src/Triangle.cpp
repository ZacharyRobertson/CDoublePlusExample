#include "Triangle.h"

void Triangle::Start()
{
	//Generate the buffers
	glGenBuffers(1, &vertBuffer);
	//Bind the buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Triangle::Update()
{
	M = rotate<float>(glfwGetTime() * 20, vec3(0, 0, 1));
	// V = ... (Camera view goes here)
	P = ortho<float>(-1, 1, 1, -1);
	MVP = P * M; //or P * V * M
}

void Triangle::Draw(GLuint program)
{
	//Get the shader locations of all the uniforms and attributes
	mvpLocation = glGetUniformLocation(program, "MVP");
	vPosLocation = glGetAttribLocation(program, "vPos");
	vColLocation = glGetAttribLocation(program, "vCol");

	//enable the shader vallues
	glEnableVertexAttribArray(vPosLocation);
	glEnableVertexAttribArray(vColLocation);

	//Send the information of our verticies over to the graphics card
	glVertexAttribPointer(vPosLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glVertexAttribPointer(vColLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 2));

	//Give the graphics card the matrix
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, (const GLfloat*)&MVP);

	//Tell the graphics card to draw it
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
