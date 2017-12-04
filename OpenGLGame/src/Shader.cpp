#include "Shader.h"

#include <string>
#include <vector>

Shader::Shader(string fileName, ShaderType type)
{
	// Store the type in class
	this->type = type;

	//Get full path
	string fullPath = "shaders/" + fileName;

	//Load the file
	ifstream shaderFile(fullPath);

	//If the file did not open
	if (!shaderFile.is_open())
	{
		cout << "Error: Could not find the shader file '" << fileName.c_str() << endl;
		system("pause");
	}
	
	// Read contents of file into string
	string tempContents;
	string contents;
	while (!shaderFile.eof())
	{
		// Get next line of file
		getline(shaderFile, tempContents);
		// Add new line to content string
		contents += tempContents;
		contents += "\n"; //Add a new line to the end
	}

	size_t size = contents.length();
	shaderText = new char[size]; //Allocate our text to store contents
	//Loop through contents
	for (size_t i = 0; i < size; i++)
	{
		// Assign contents to our allocated text
		shaderText[i] = contents[i];
	}

	//Add the null terminator to the end of the text
	shaderText[size - 1] = '\0';

	//Close the file once we're done!
	shaderFile.close();
}

void Shader::Compile()
{
	switch (type)
	{
	case VERTEX:
		handle = glCreateShader(GL_VERTEX_SHADER);
		break;
	case FRAGMENT:
		handle = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		break;
	}
	// Tell the graphics card where the shader's text is stored
	glShaderSource(handle, 1, &shaderText, NULL);
	//Compile the shader
	glCompileShader(handle);

	//Check for errors
	GLint isCompiled = 0;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &isCompiled);
	//Did the shader fail to compile
	if (isCompiled == GL_FALSE)
	{
		//Get the length of the error log (lines)
		GLint maxLength = 0;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &maxLength);
		//Create a list (vector) that contains all the characters
		vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(handle, maxLength, &maxLength, &errorLog[0]);
		for (unsigned int i = 0; i < errorLog.size(); i++)
		{
			// Print the error log to console
			cout << errorLog[i];
		}
		// Delete the shader if there is an error
		glDeleteShader(handle);
		return;
	}
}
