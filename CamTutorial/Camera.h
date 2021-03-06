#pragma once
#include "glm/glm.hpp"
class Camera
{
public:

	Camera();
	~Camera();

	virtual void update(float deltaTime);

	glm::mat4 GetViewMatrix();

	glm::mat4 GetProjectionMatrix(float w, float h);

protected:

private:

	float m_theta;
	float m_phi;
	glm::vec3 m_position;
	float m_lastMouseX;
	float m_lastMouseY;


	

};

