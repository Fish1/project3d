#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <stdlib.h> // exit();
#include <math.h>
#include <stdio.h> 

#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

GLuint linkShaders(GLuint vertexShader, GLuint fragmentShader);

void errorCallback(int error, const char * description)
{
	printf("Error: %s\n", description);
}

int main(void)
{
	glfwSetErrorCallback(errorCallback);

	if(!glfwInit())
	{
		printf("glfw init failed. \n");

		return 1;
	}

	GLFWwindow * window = glfwCreateWindow(640, 480, "mygame", nullptr, nullptr);

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

	// ENABLE CULLING
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	// ENABLE DEPTH
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.0f);

	// CREATE SHADERS
	Shader vertexShader(GL_VERTEX_SHADER, "shader.vs");
	Shader fragmentShader(GL_FRAGMENT_SHADER, "shader.fs");
	GLuint shaderProgram = linkShaders(vertexShader.getHandle(),
					fragmentShader.getHandle());
	// FIND UNIFORM VARIABLES
	GLint u_modelViewProjection = glGetUniformLocation(shaderProgram, "u_modelViewProjection");
	GLint u_normal = glGetUniformLocation(shaderProgram, "u_normal");
	GLint u_light_pos = glGetUniformLocation(shaderProgram, "u_light_pos");

	// CREATE MODEL
	Model model;

	// CREATE PROJECTION
	glm::mat4 projection = glm::perspective(45.0f, 640.0f / 480.0f, 0.01f, 100.0f);

	// CREATE CAMERA
	Camera camera;
	camera.rotate(-M_PI / 4.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	// LIGHT POSITION
	glm::vec3 light = glm::vec3(0.0f, 3.0f, -3.0f);

	while(!glfwWindowShouldClose(window))
	{
		// CLEAR SCREEN
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// USE SHADER
		glUseProgram(shaderProgram);
	
		// CREATE MODEL MATRIX	
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, -3.0f));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		glm::mat4 modelMatrix = translate * rotate * scale;

		// SET MATRIX MODEL VIEW
		glm::mat4 modelViewProjection = projection * camera.getView() * modelMatrix;
		glUniformMatrix4fv(u_modelViewProjection, 1, GL_FALSE, glm::value_ptr(modelViewProjection));
		
		// SET MATRIX NORMAL
		glUniformMatrix4fv(u_normal, 1, GL_FALSE, glm::value_ptr(rotate));

		// SET LIGHT
		glUniform3f(u_light_pos, light.x, light.y, light.z); 

		// TURN ON VERTICES AND NORMALS
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		// POINT TO MODEL DATA
		glVertexPointer(3, GL_FLOAT, 0, model.getVertices());
		glNormalPointer(GL_FLOAT, 0, model.getNormals());

		// DRAW TRIANGLE USING INDEXES
		glDrawElements(GL_TRIANGLES, model.getIndexCount(), GL_UNSIGNED_INT, model.getIndexes());

		// TURN OFF VERTICES AND NORMALS
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

		// SHOW SCREEN
		glfwSwapBuffers(window);

		// POLL EVENTS
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
