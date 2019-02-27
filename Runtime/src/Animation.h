#pragma once
#include "Keyframe.h"
#include <vector>

class Animation
{
public:
	Animation();
	Animation(void *p_property, PropertyType p_type);
	bool EvaluateBool(double time, bool updateProperty = true);
	int EvaluateInt(double time, bool updateProperty = true);
	float EvaluateFloat(double time, bool updateProperty = true);
	double EvaluateDouble(double time, bool updateProperty = true);
	int InsertKeyframe(Keyframe k);										// keep this vector of Keyframes sorted by time
	void DeleteKeyframe(int index);
private:
	std::vector<Keyframe> keyframes;
	void *property;
	PropertyType type;
};