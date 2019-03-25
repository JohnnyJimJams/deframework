#include "Material.h"

MaterialProperty::MaterialProperty(bool bVal)
{
	type = MaterialPropertyType::BOOL_VAL;
	value.boolValue = bVal;
}

MaterialProperty::MaterialProperty(float fVal)
{
	type = MaterialPropertyType::FLOAT_VAL;
	value.floatValue = fVal;
}

MaterialProperty::MaterialProperty(glm::vec2 v2Val)
{
	type = MaterialPropertyType::VEC2_VAL;
	value.vec2Value = v2Val;
}

MaterialProperty::MaterialProperty(glm::vec3 v3Val)
{
	type = MaterialPropertyType::VEC3_VAL;
	value.vec3Value = v3Val;
}

MaterialProperty::MaterialProperty(glm::vec4 v4Val)
{
	type = MaterialPropertyType::VEC4_VAL;
	value.vec4Value = v4Val;
}

MaterialProperty::MaterialProperty(std::string sVal)
{
	type = MaterialPropertyType::TEXTURE2D_VAL;
	value.textureName = sVal;
}

Material::Material()
{
}

Material::~Material()
{
}
