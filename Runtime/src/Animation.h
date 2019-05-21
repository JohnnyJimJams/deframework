#pragma once
#include "Keyframe.h"
#include <vector>
#include <string>

class Animation
{
public:
	Animation();
	Animation(std::string p_id, void *p_property, KeyframePropertyType p_type);
	bool EvaluateBool(double time, bool updateProperty = true);
	int EvaluateInt(double time, bool updateProperty = true);
	float EvaluateFloat(double time, bool updateProperty = true);
	double EvaluateDouble(double time, bool updateProperty = true);
	glm::vec3 EvaluateVec3(double time, bool updateProperty = true);
	glm::quat EvaluateQuat(double time, bool updateProperty = true);
	int InsertKeyframe(Keyframe k);										// keep this vector of Keyframes sorted by time
	void DeleteKeyframe(int index);
	std::vector<Keyframe> GetKeyframes();
	KeyframePropertyType GetType();
	bool compareProperty(std::string prop);
private:
	std::string id;	// EntityName.PropertyName
	std::vector<Keyframe> keyframes;
	void *property;
	KeyframePropertyType type;
};