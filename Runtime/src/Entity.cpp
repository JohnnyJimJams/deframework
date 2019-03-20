#include "Entity.h"
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

Entity::Entity()
{
	Position = glm::vec3();
	Rotation = glm::quat();
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Entity::~Entity()
{
}

glm::mat4 Entity::GetModelMatrix()
{
	glm::mat4 ModelMatrix = glm::mat4(1.0f);

	ModelMatrix = glm::translate(ModelMatrix, Position);
	ModelMatrix = glm::scale(ModelMatrix, Scale);
	ModelMatrix *= toMat4(Rotation);

	return ModelMatrix;
}

glm::vec3 Entity::GetEulerAngles()
{
	return glm::eulerAngles(Rotation);
}

void Entity::SetEulerAngles(glm::vec3 euler)
{
	Rotation = glm::quat(euler);
}
