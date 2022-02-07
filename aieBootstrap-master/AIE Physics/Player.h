#pragma once
#include "Circle.h"
class Player : public Circle
{
public:

	Player(glm::vec2 a_position, glm::vec2 a_velocity,
		float a_mass, float a_radius, glm::vec4 a_colour);
	~Player();

	virtual void MakeGizmo();

	float GetRadius() { return m_radius; }
	glm::vec4 GetColour() { return m_colour; }

protected:

	float m_radius;
	glm::vec4 m_colour;

private:

};
