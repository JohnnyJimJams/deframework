#pragma once
#include "glm/vec2.hpp"

enum KeyframeHandleType
{
	AUTO
};

struct KeyframeHandle
{
	KeyframeHandle();
	KeyframeHandle(KeyframeHandleType pType, glm::vec2 pPosition);
	KeyframeHandleType type;
	glm::vec2 position;
};

enum PropertyType
{
	BOOL_VAL, DOUBLE_VAL, FLOAT_VAL, INT_VAL
};

enum KeyframeInterpolationType
{
	CONSTANT, LINEAR, CURVED
};

struct Keyframe
{
	Keyframe(double ptime, bool pBoolValue, KeyframeInterpolationType pInterpolation);
	Keyframe(double ptime, int pIntValue, KeyframeInterpolationType pInterpolation);
	Keyframe(double ptime, float pfloatValue, KeyframeInterpolationType pInterpolation, KeyframeHandle pHandleIn, KeyframeHandle pHandleOut);
	Keyframe(double ptime, double pDoubleValue, KeyframeInterpolationType pInterpolation, KeyframeHandle pHandleIn, KeyframeHandle pHandleOut);

	double time;

	PropertyType type;

	union PropertyValue {
		bool boolValue;
		float floatValue;
		double doubleValue;
		int intValue;
	};
	PropertyValue value;
	KeyframeInterpolationType interpolation;
	KeyframeHandle in;
	KeyframeHandle out;
};