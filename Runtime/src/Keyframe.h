#pragma once
#include "glm/vec2.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

enum class KeyframeHandleType
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

enum class KeyframePropertyType
{
	BOOL_VAL, DOUBLE_VAL, FLOAT_VAL, INT_VAL, VEC3_VAL, QUAT_VAL
};

enum class KeyframeInterpolationType
{
	CONSTANT, LINEAR, CURVED
};

struct Keyframe
{
	Keyframe(double ptime, bool pBoolValue, KeyframeInterpolationType pInterpolation);
	Keyframe(double ptime, int pIntValue, KeyframeInterpolationType pInterpolation);
	Keyframe(double ptime, float pfloatValue, KeyframeInterpolationType pInterpolation, KeyframeHandle pHandleIn, KeyframeHandle pHandleOut);
	Keyframe(double ptime, double pDoubleValue, KeyframeInterpolationType pInterpolation, KeyframeHandle pHandleIn, KeyframeHandle pHandleOut);
	Keyframe(double ptime, glm::vec3 pVec3Value, KeyframeInterpolationType pInterpolation, KeyframeHandle pHandleIn, KeyframeHandle pHandleOut);
	Keyframe(double ptime, glm::quat pQuatValue, KeyframeInterpolationType pInterpolation, KeyframeHandle pHandleIn, KeyframeHandle pHandleOut);

	double time;

	union PropertyValue {
		bool boolValue;
		float floatValue;
		double doubleValue;
		int intValue;
		glm::vec3 vec3Value;
		glm::quat quatValue;
	};
	PropertyValue value;
	KeyframeInterpolationType interpolation;
	KeyframeHandle in;
	KeyframeHandle out;
};