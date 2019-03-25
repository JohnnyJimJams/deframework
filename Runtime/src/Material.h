#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>

enum class MaterialPropertyType
{
	BOOL_VAL, FLOAT_VAL, VEC2_VAL, VEC3_VAL, VEC4_VAL, TEXTURE2D_VAL
};

struct MaterialProperty
{
	MaterialProperty(bool bVal);
	MaterialProperty(float fVal);
	MaterialProperty(glm::vec2 v2Val);
	MaterialProperty(glm::vec3 v3Val);
	MaterialProperty(glm::vec4 v4Val);
	MaterialProperty(std::string sVal);

	MaterialPropertyType type;

	struct MaterialPropertyValue { // This has to be a struct cause we want to include a std::string, which union can't do
		bool boolValue;
		float floatValue;
		glm::vec2 vec2Value;
		glm::vec3 vec3Value;
		glm::vec4 vec4Value;
		std::string textureName;
	};
	MaterialPropertyValue value;
};

class Material
{
public:
	Material();
	~Material();
	std::string ShaderName;
private:
	std::vector<MaterialProperty> m_properties;
};

