#pragma once
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

class EImage: public Entity
{
public:
	EImage();
	~EImage();
	std::string GetType() { return "Image"; }

protected:

};
