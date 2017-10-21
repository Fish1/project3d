#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Vertex 
{ 
	GLfloat x; 
	GLfloat y; 
	GLfloat z;
};

typedef Vertex Normal;

class Model
{
private:

	Vertex * m_vertices;

	Normal * m_normals;

	GLuint m_vertexCount;

public:

	Model();

	Vertex * getVertices();

	Normal * getNormals();

	GLuint getVertexCount();

};

#endif
