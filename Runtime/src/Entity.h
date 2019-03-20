#ifndef __ENTITY_H_
#define __ENTITY_H_

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Entity
{
public:
	Entity();
	~Entity();
	glm::vec3 Position;
	glm::quat Rotation;
	glm::vec3 Scale;
	glm::mat4 GetModelMatrix();
	glm::vec3 GetEulerAngles();
	void SetEulerAngles(glm::vec3 euler);
private:

};

#endif // __ENTITY_H_