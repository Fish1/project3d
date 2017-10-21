#include <GL/glew.h>

#include <string>

class Shader
{
private:
	
	GLuint m_handle;

	std::string m_src;

	void compile(GLenum type);

public:
	Shader(GLenum type, std::string filename);

	GLuint getHandle();
};
