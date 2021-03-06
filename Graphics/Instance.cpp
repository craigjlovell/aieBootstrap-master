#include "Instance.h"

#include "glm/ext.hpp"

#include "Scene.h"
#include "Texture.h"
#include "OBJMesh.h"
#include "Camera.h"
#include "GraphicsApp.h"
#include "Mesh.h"
#include "Shader.h"

Instance::Instance(glm::mat4 a_transform, aie::OBJMesh* a_mesh, aie::ShaderProgram* a_shader) :
	m_transform(a_transform), m_mesh(a_mesh), m_shader(a_shader)
{

}

Instance::Instance(glm::vec3 a_position, glm::vec3 a_rotation, glm::vec3 a_scale, aie::OBJMesh* a_mesh, aie::ShaderProgram* a_shader) :
	m_mesh(a_mesh), m_shader(a_shader)
{
	m_rotation = a_rotation;
	m_transform = MakeTransform(a_position, a_rotation, a_scale);
}

void Instance::Draw(Scene* a_scene)
{
	// Set the render pipeline 
	m_shader->bind();

	// Bind the transforms and other relevant uniforms
	auto pvm = a_scene->GetCamera()->
		GetProjectionMatrix(a_scene->GetWindowSize().x,
							a_scene->GetWindowSize().y) 
		* a_scene->GetCamera()->GetViewMatrix() * m_transform;

	m_shader->bindUniform("ProjectionViewModel", pvm);
	m_shader->bindUniform("ModelMatrix", m_transform);

	// Bind the lighting and camera uniforms
	m_shader->bindUniform("AmbientColor", a_scene->GetAmibentLight());
	m_shader->bindUniform("LightColor", a_scene->GetGlobalLight().color);
	m_shader->bindUniform("LightDirection", a_scene->GetGlobalLight().direction);

	m_shader->bindUniform("CameraPosition", a_scene->GetCamera()->GetPosition());
	
	int numberOfLights = a_scene->GetNumLights();
	m_shader->bindUniform("numLights", numberOfLights);
	m_shader->bindUniform("PointLightPositions", numberOfLights, a_scene->GetPointLightPositions());
	m_shader->bindUniform("PointLightColors", numberOfLights, a_scene->GetPointLightColors());
	
	// Draw the mesh
	m_mesh->draw();
}

glm::mat4 Instance::MakeTransform(glm::vec3 a_position, glm::vec3 a_rotation, glm::vec3 a_scale)
{
	glm::vec3 test = glm::vec3(0);
		m_rotation = a_rotation;
	return glm::translate(glm::mat4(1), a_position)
		* glm::rotate(glm::mat4(1),
			glm::radians(a_rotation.x), glm::vec3(1, 0, 0))
		* glm::rotate(glm::mat4(1),
			glm::radians(a_rotation.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1),
			glm::radians(a_rotation.z), glm::vec3(0, 0, 1))
		* glm::scale(glm::mat4(1), a_scale);
}

//void Instance::SetRotation(glm::vec3 a_rotation)
//{
//	glm::quat quaternion = glm::quat_cast(m_transform); 
//	glm::vec3 euler = glm::degrees(glm::eulerAngles(quaternion)); 
//	float eulerRot[] = { euler.x, euler.y, euler.z };
//	return;
//}
