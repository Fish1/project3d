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

typedef GLuint Index;

class Model
{
private:

	Vertex * m_vertices;

	Normal * m_normals;

	Index * m_indexes;

	GLuint m_vertexCount;

	GLuint m_indexCount;

public:

	Model();

	Vertex * getVertices();

	Normal * getNormals();

	Index * getIndexes();

	GLuint getVertexCount();

	GLuint getIndexCount();

private:

	void create_box();

	void create_plane();

};

#endif
