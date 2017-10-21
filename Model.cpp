#include "Model.hpp"

Model::Model()
{
	m_vertexCount = 18;
	m_vertices = new Vertex[18];

	// FRONT	
	m_vertices[0] = {-0.5f, -0.5f, 0.5f};
	m_vertices[1] = {-0.5f,  0.5f, 0.5f};
	m_vertices[2] = { 0.5f,  0.5f, 0.5f};

	m_vertices[3] = {-0.5f, -0.5f, 0.5f};
	m_vertices[4] = {0.5f, 0.5f, 0.5f};
	m_vertices[5] = {0.5f, -0.5f, 0.5f};

	// BACK	
	m_vertices[6] = {-0.5f, -0.5f, -0.5f};
	m_vertices[7] = {-0.5f,  0.5f, -0.5f};
	m_vertices[8] = {0.5f,  0.5f, -0.5f};

	m_vertices[9] = {-0.5f, -0.5f, -0.5f};
	m_vertices[10] = {0.5f, 0.5f, -0.5f};
	m_vertices[11] = {0.5f, -0.5f, -0.5f};

	// RIGHT
	m_vertices[12] = {0.5f, -0.5f, 0.5f};
	m_vertices[13] = {0.5f,  0.5f, -0.5f};
	m_vertices[14] = {0.5f,  0.5f, 0.5f};

	m_vertices[15] = {0.5f, -0.5f, 0.5f};
	m_vertices[16] = {0.5f, -0.5f, -0.5f};
	m_vertices[17] = {0.5f, 0.5f, -0.5f};

	m_normals = new Normal[18];
	
	// FRONT NORMAL
	m_normals[0] = {0.0f, 0.0f, 1.0f};
	m_normals[1] = {0.0f, 0.0f, 1.0f};
	m_normals[2] = {0.0f, 0.0f, 1.0f};
	m_normals[3] = {0.0f, 0.0f, 1.0f};
	m_normals[4] = {0.0f, 0.0f, 1.0f};
	m_normals[5] = {0.0f, 0.0f, 1.0f};

	// BACK NORMAL	
	m_normals[5] = {0.0f, 0.0f, -1.0f};
	m_normals[6] = {0.0f, 0.0f, -1.0f};
	m_normals[7] = {0.0f, 0.0f, -1.0f};
	m_normals[8] = {0.0f, 0.0f, -1.0f};
	m_normals[9] = {0.0f, 0.0f, -1.0f};
	m_normals[10] = {0.0f, 0.0f, -1.0f};

	// RIGHT NORMAL	
	m_normals[11] = {1.0f, 0.0f, 0.0f};
	m_normals[12] = {1.0f, 0.0f, 0.0f};
	m_normals[13] = {1.0f, 0.0f, 0.0f};
	m_normals[14] = {1.0f, 0.0f, 0.0f};
	m_normals[15] = {1.0f, 0.0f, 0.0f};
	m_normals[16] = {1.0f, 0.0f, 0.0f};
}

Vertex * Model::getVertices()
{
	return m_vertices;
}

Vertex * Model::getNormals()
{
	return m_normals;
}

GLuint Model::getVertexCount()
{
	return m_vertexCount;
}
