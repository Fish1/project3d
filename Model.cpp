#include "Model.hpp"

#include <stdio.h>

#include <glm/glm.hpp>
#include <math.h>

Model::Model()
{
//	create_box();
	create_plane();
}

float calcY(float x, float z)
{
	return 0.0f;
	//return cos(x) - sin(z);
}

void Model::create_plane()
{
	int sizeX = 10;
	int sizeZ = 10;
	m_vertexCount = (sizeX * sizeZ) * 4;
	m_vertices = new Vertex[m_vertexCount];
	m_normals = new Normal[m_vertexCount];
	m_indexCount = (sizeX * sizeZ) * 6;
	m_indexes = new Index[m_indexCount];


	unsigned int vertex_i = 0;
	unsigned int index_i = 0;
	float stepX = 1.0f;
	float stepZ = 1.0f;

	for(int x = 0; x < sizeX; ++x)
	{
		for(int z = 0; z < sizeZ; ++z)
		{
			float dx = (float)x * stepX;
			float dz = (float)z * stepZ;

			float px = 0.0f + dx;
			float pz = 0.0f - dz;
			float py = calcY(px, pz);
			m_vertices[vertex_i++] = {px, py, pz};

			px = 1.0f + dx;
			pz = 0.0f - dz;
			py = calcY(px, pz);
			m_vertices[vertex_i++] = {px, py, pz};

			px = 1.0f + dx;
			pz = -1.0f - dz;
			py = calcY(px, pz);
			m_vertices[vertex_i++] = {px, py, pz};

			px = 0.0f + dx;
			pz = -1.0f - dz;
			py = calcY(px, pz);
			m_vertices[vertex_i++] = {px, py, pz};

			Vertex a = m_vertices[vertex_i - 4];
			glm::vec3 va = glm::vec3(a.x, a.y, a.z);
			
			a = m_vertices[vertex_i - 3];
			glm::vec3 vb = glm::vec3(a.x, a.y, a.z);
		
			a = m_vertices[vertex_i - 2];
			glm::vec3 vc = glm::vec3(a.x, a.y, a.z);
		
			a = m_vertices[vertex_i - 1];
			glm::vec3 vd = glm::vec3(a.x, a.y, a.z);

			glm::vec3 n = glm::normalize(glm::cross(vb - va, vd - va));
			m_normals[vertex_i - 4] = {n.x, n.y, n.z};
			m_normals[vertex_i - 3] = {n.x, n.y, n.z};
			m_normals[vertex_i - 2] = {n.x, n.y, n.z};
			m_normals[vertex_i - 1] = {n.x, n.y, n.z};

			m_indexes[index_i++] = vertex_i - 4;
			m_indexes[index_i++] = vertex_i - 2;
			m_indexes[index_i++] = vertex_i - 1;
			m_indexes[index_i++] = vertex_i - 4;
			m_indexes[index_i++] = vertex_i - 3;
			m_indexes[index_i++] = vertex_i - 2;
		}
	}
/*
	// Floor
	m_vertices[0] = {-0.5f, 0.0f, 0.5f};
	m_vertices[1] = {0.5f, 0.0f, -0.5f};
	m_vertices[2] = {-0.5f, 0.0f, -0.5f};
	m_vertices[3] = {-0.5f, 0.0f, 0.5f};
	m_vertices[4] = {0.5f, 0.0f, 0.5f};
	m_vertices[5] = {0.5f, 0.0f, -0.5f};

	m_normals = new Normal[m_vertexCount];

	// Floor
	m_normals[0] = {0.0f, 1.0f, 0.0f};
	m_normals[1] = {0.0f, 1.0f, 0.0f};
	m_normals[2] = {0.0f, 1.0f, 0.0f};
	m_normals[3] = {0.0f, 1.0f, 0.0f};
	m_normals[4] = {0.0f, 1.0f, 0.0f};
	m_normals[5] = {0.0f, 1.0f, 0.0f};
	*/
}

void Model::create_box()
{
	m_vertexCount = 36;
	m_vertices = new Vertex[m_vertexCount];

	// FRONT	
	m_vertices[0] = {-0.5f, -0.5f, 0.5f};
	m_vertices[1] = {0.5f,  0.5f, 0.5f};
	m_vertices[2] = {-0.5f,  0.5f, 0.5f};

	m_vertices[3] = {-0.5f, -0.5f, 0.5f};
	m_vertices[4] = {0.5f, -0.5f, 0.5f};
	m_vertices[5] = {0.5f, 0.5f, 0.5f};

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
	
	// LEFT 
	m_vertices[18] = {-0.5f, -0.5f, -0.5f};
	m_vertices[19] = {-0.5f,  0.5f, 0.5f};
	m_vertices[20] = {-0.5f,  0.5f, -0.5f};

	m_vertices[21] = {-0.5f, -0.5f, -0.5f};
	m_vertices[22] = {-0.5f, -0.5f, 0.5f};
	m_vertices[23] = {-0.5f, 0.5f, 0.5f};

	// TOP
	m_vertices[24] = {-0.5f, 0.5f, 0.5f};
	m_vertices[25] = {0.5f, 0.5f, -0.5f};
	m_vertices[26] = {-0.5f, 0.5f, -0.5f};
	
	m_vertices[27] = {-0.5f, 0.5f, 0.5f};
	m_vertices[28] = {0.5f, 0.5f, 0.5f};
	m_vertices[29] = {0.5f, 0.5f, -0.5f};

	// BOTTOM
	m_vertices[30] = {-0.5f, -0.5f, 0.5f};
	m_vertices[31] = {-0.5f, -0.5f, -0.5f};
	m_vertices[32] = {0.5f, -0.5f, -0.5f};
	
	m_vertices[33] = {-0.5f, -0.5f, 0.5f};
	m_vertices[34] = {0.5f, -0.5f, -0.5f};
	m_vertices[35] = {0.5f, -0.5f, 0.5f};

	m_normals = new Normal[m_vertexCount];
	
	// FRONT NORMAL
	m_normals[0] = {0.0f, 0.0f, 1.0f};
	m_normals[1] = {0.0f, 0.0f, 1.0f};
	m_normals[2] = {0.0f, 0.0f, 1.0f};
	m_normals[3] = {0.0f, 0.0f, 1.0f};
	m_normals[4] = {0.0f, 0.0f, 1.0f};
	m_normals[5] = {0.0f, 0.0f, 1.0f};

	// BACK NORMAL	
	m_normals[6] = {0.0f, 0.0f, -1.0f};
	m_normals[7] = {0.0f, 0.0f, -1.0f};
	m_normals[8] = {0.0f, 0.0f, -1.0f};
	m_normals[9] = {0.0f, 0.0f, -1.0f};
	m_normals[10] = {0.0f, 0.0f, -1.0f};
	m_normals[11] = {0.0f, 0.0f, -1.0f};

	// RIGHT NORMAL	
	m_normals[12] = {1.0f, 0.0f, 0.0f};
	m_normals[13] = {1.0f, 0.0f, 0.0f};
	m_normals[14] = {1.0f, 0.0f, 0.0f};
	m_normals[15] = {1.0f, 0.0f, 0.0f};
	m_normals[16] = {1.0f, 0.0f, 0.0f};
	m_normals[17] = {1.0f, 0.0f, 0.0f};

	// LEFT NORMAL
	m_normals[18] = {-1.0f, 0.0f, 0.0f};
	m_normals[19] = {-1.0f, 0.0f, 0.0f};
	m_normals[20] = {-1.0f, 0.0f, 0.0f};
	m_normals[21] = {-1.0f, 0.0f, 0.0f};
	m_normals[22] = {-1.0f, 0.0f, 0.0f};
	m_normals[23] = {-1.0f, 0.0f, 0.0f};

	// TOP NORMAL
	m_normals[24] = {0.0f, 1.0f, 0.0f};
	m_normals[25] = {0.0f, 1.0f, 0.0f};
	m_normals[26] = {0.0f, 1.0f, 0.0f};
	m_normals[27] = {0.0f, 1.0f, 0.0f};
	m_normals[28] = {0.0f, 1.0f, 0.0f};
	m_normals[29] = {0.0f, 1.0f, 0.0f};

	// BOTTOM NORMAL
	m_normals[30] = {0.0f, -1.0f, 0.0f};
	m_normals[31] = {0.0f, -1.0f, 0.0f};
	m_normals[32] = {0.0f, -1.0f, 0.0f};
	m_normals[33] = {0.0f, -1.0f, 0.0f};
	m_normals[34] = {0.0f, -1.0f, 0.0f};
	m_normals[35] = {0.0f, -1.0f, 0.0f};

}


Vertex * Model::getVertices()
{
	return m_vertices;
}

Vertex * Model::getNormals()
{
	return m_normals;
}

Index * Model::getIndexes()
{
	return m_indexes;
}

GLuint Model::getVertexCount()
{
	return m_vertexCount;
}

GLuint Model::getIndexCount()
{
	return m_indexCount;
}
