#pragma once
#include "Mesh.h"
#include "Entity.h"
/*
class Entity
{
public:
	Entity();
	virtual ~Entity();
	bool Active;
	std::string Name;
	glm::vec3 Position;
	glm::quat Rotation;
	glm::vec3 Scale;
	glm::mat4 GetModelMatrix();
	glm::vec3 GetEulerAngles();
	void SetEulerAngles(glm::vec3 euler);
	virtual std::string GetType() = 0;
protected:
	bool ScreenSpace;*/

class EMesh: public Entity
{
public:
	EMesh();
	~EMesh();
	std::string GetType() { return "Mesh"; }
	Mesh *GetMesh() { return m_mesh; }
	void SetMesh(Mesh *mesh) { m_mesh = mesh; }
protected:
	Mesh *m_mesh;
};
