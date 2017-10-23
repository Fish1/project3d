#include <glm/glm.hpp>

class Camera
{
private:
	
	glm::vec3 m_position;

	glm::vec3 m_direction;

	glm::vec3 m_up;

public:

	Camera();

	glm::mat4 getView();

	void rotate(float angle, glm::vec3 axis);

};
