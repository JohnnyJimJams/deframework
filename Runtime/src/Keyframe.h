#pragma once
#include "Eigen/Core"

enum KeyframeHandleType
{
	Constant, Linear, Smooth, User
};

struct KeyframeHandle
{
	KeyframeHandle();
	KeyframeHandle(KeyframeHandleType pType, Eigen::Vector2f pPosition);
	KeyframeHandleType type;
	Eigen::Vector2f position;
};

enum PropertyType
{
	BOOL_VAL, DOUBLE_VAL, FLOAT_VAL, INT_VAL
};

struct Keyframe
{
	Keyframe(double ptime, bool pBoolValue);
	Keyframe(double ptime, int pIntValue);
	Keyframe(double ptime, float pfloatValue, KeyframeHandle pHandleIn, KeyframeHandle pHandleOut);
	Keyframe(double ptime, double pDoubleValue, KeyframeHandle pHandleIn, KeyframeHandle pHandleOut);

	double time;

	PropertyType type;

	union PropertyValue {
		bool boolValue;
		float floatValue;
		double doubleValue;
		int intValue;
	};
	PropertyValue value;

	KeyframeHandle in;
	KeyframeHandle out;
};