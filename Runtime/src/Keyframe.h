#pragma once
#include "Eigen/Core"

enum KeyframeHandleType
{
	None, Smooth, Constant, Linear, User
};

struct KeyframeHandle
{
	KeyframeHandle();
	KeyframeHandleType type;
	Eigen::Vector2f position;
};

enum KeyframeType
{
	BOOL_VAL, DOUBLE_VAL, FLOAT_VAL, INT_VAL
};

struct Keyframe
{
	Keyframe();

	double time;

	KeyframeType type;
	bool boolValue;
	float floatValue;
	double doubleValue;
	int intValue;

	KeyframeHandle in;
	KeyframeHandle out;
};