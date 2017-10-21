#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdlib.h> // exit();
#include <stdio.h>

#include "Model.hpp"
#include "Shader.hpp"

GLuint linkShaders(GLuint vertexShader, GLuint fragmentShader);

int main(void)
{
	if(!glfwInit())
	{
		printf("glew init failed. \n");

		return 1;
	}

	GLFWwindow * window = glfwCreateWindow(600, 600, "OpenGL", nullptr, nullptr);

	if(!window)
	{
		printf("create window failed. \n");

		return 1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK)
	{
		printf("glew init failed. \n");

		return 1;
	}

	glDepthMask(GL_TRUE);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	Shader vertexShader(GL_VERTEX_SHADER, "shader.vs");

	Shader fragmentShader(GL_FRAGMENT_SHADER, "shader.fs");

	GLuint shaderProgram = linkShaders(vertexShader.getHandle(),
					fragmentShader.getHandle());

	Model model;

	GLint u_model = glGetUniformLocation(shaderProgram, "u_model");
	
	GLint u_red = glGetUniformLocation(shaderProgram, "u_red");
	GLint u_green = glGetUniformLocation(shaderProgram, "u_green");
	GLint u_blue = glGetUniformLocation(shaderProgram, "u_blue");

	GLint u_light_pos = glGetUniformLocation(shaderProgram, "u_light_pos");

	glm::mat4 projection = glm::perspective(35.0f, 1.0f / 2.0f, 0.1f, 100.0f);

	float r_red = 0.003f;
	float red = 0.0f;

	float r_green = 0.002f;
	float green = 0.5f;

	float r_blue = 0.001f;
	float blue = 1.0f;

	float x = -1.0f;
	float rot = 0.0f;

	glm::vec4 light = glm::vec4(-2.0f, 0.0f, -1.0f, 1.0f);

	while(!glfwWindowShouldClose(window))
	{
		// CLEAR SCREEN
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// USE SHADER
		glUseProgram(shaderProgram);
	
		// CREATE MATRIX	
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), rot += 0.01f, glm::vec3(1.0f, 1.0f, 1.0f));
		
		glm::mat4 modelMatrix = transform * rotate * scale;

		// SET MATRIX
		glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(projection * modelMatrix));

		// SET LIGHT
		glUniform4f(u_light_pos, light.x, light.y, light.z, light.w); 

		// SET COLOR	
		red += r_red;
		if(red > 1.0f || red < 0.0f) r_red *= -1.0f;
		glUniform1f(u_red, red);

		green += r_green;
		if(green > 1.0f || green < 0.0f) r_green *= -1.0f;
		glUniform1f(u_green, green);
		
		blue += r_blue;
		if(blue > 1.0f || blue < 0.0f) r_blue *= -1.0f;
		glUniform1f(u_blue, blue);

		// TURN ON VERTICES AND COLORS
		glEnableClientState(GL_VERTEX_ARRAY);

		// POINT TO TRIANGLE DATA
		glVertexPointer(3, GL_FLOAT, 0, model.getVertices());
		glNormalPointer(GL_FLOAT, 0, model.getNormals());

		// DRAW TRIANGLE
		glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());

		// TURN OFF VERTICES AND COLORS
		glDisableClientState(GL_VERTEX_ARRAY);

		// SHOW SCREEN
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
}

GLuint linkShaders(GLuint vertexShader, GLuint fragmentShader)
{
	// Create program object
	GLuint programID = glCreateProgram();

	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);

	glLinkProgram(programID);

	return programID;
}
