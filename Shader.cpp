#include "Shader.hpp"

#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>

void Shader::compile(GLenum type)
{
	GLuint shader; 
	GLint compiled;

	// Create shader object
	m_handle = glCreateShader(type);

	// Shader creation failed?
	if(m_handle == 0)
	{
		exit(1);	
	}
	
	// Load shader source
	const char * c_src = m_src.c_str();
	glShaderSource(m_handle, 1, &c_src, NULL);
	
	// Compile shader
	glCompileShader(m_handle);
	
	// Check compiled status
	glGetShaderiv(m_handle, GL_COMPILE_STATUS, &compiled);

	if(!compiled)
	{
		GLchar * err;

		glGetShaderInfoLog(m_handle, 10000, NULL, err);

		printf("%s\n", err);

		exit(1);	
	}
}

Shader::Shader(GLenum type, std::string filename)
{
	std::ifstream file;
	file.open(filename);

	std::string line;

	while(std::getline(file, line))
	{
		m_src += line + "\n";	
	}

	compile(type);
}

GLuint Shader::getHandle()
{
	return m_handle;
}

