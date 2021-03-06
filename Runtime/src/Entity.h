#ifndef __ENTITY_H_
#define __ENTITY_H_

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>

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
	bool ScreenSpace;
};

#endif // __ENTITY_H_