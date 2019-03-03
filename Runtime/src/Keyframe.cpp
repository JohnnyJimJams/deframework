#include "Keyframe.h"

KeyframeHandle::KeyframeHandle()
{
	type = KeyframeHandleType::AUTO;
	position = Eigen::Vector2f(0, 0);
}

KeyframeHandle::KeyframeHandle(KeyframeHandleType pType, Eigen::Vector2f pPosition)
{
	type = pType;
	position = pPosition;
}

Keyframe::Keyframe(double pTime, bool pBoolValue, KeyframeInterpolationType pInterpolation)
{
	time = pTime;
	value.boolValue = pBoolValue;
	interpolation = pInterpolation;
}

Keyframe::Keyframe(double pTime, int pIntValue, KeyframeInterpolationType pInterpolation)
{
	time = pTime;
	value.intValue = pIntValue;
	interpolation = pInterpolation;
}

Keyframe::Keyframe(double pTime, float pfloatValue, KeyframeInterpolationType pInterpolation, KeyframeHandle pHandleIn, KeyframeHandle pHandleOut)
{
	time = pTime;
	value.floatValue = pfloatValue;
	interpolation = pInterpolation;
	in = pHandleIn;
	out = pHandleOut;
}

Keyframe::Keyframe(double pTime, double pDoubleValue, KeyframeInterpolationType pInterpolation, KeyframeHandle pHandleIn, KeyframeHandle pHandleOut)
{
	time = pTime;
	value.doubleValue = pDoubleValue;
	interpolation = pInterpolation;
	in = pHandleIn;
	out = pHandleOut;
}