#include "Keyframe.h"

KeyframeHandle::KeyframeHandle()
{
	type = KeyframeHandleType::Constant;
	position = Eigen::Vector2f(0, 0);
}

KeyframeHandle::KeyframeHandle(KeyframeHandleType pType, Eigen::Vector2f pPosition)
{
	type = pType;
	position = pPosition;
}

Keyframe::Keyframe(double pTime, bool pBoolValue)
{
	time = pTime;
	value.boolValue = pBoolValue;
}

Keyframe::Keyframe(double pTime, int pIntValue)
{
	time = pTime;
	value.intValue = pIntValue;
}

Keyframe::Keyframe(double pTime, float pfloatValue, KeyframeHandle pHandleIn, KeyframeHandle pHandleOut)
{
	time = pTime;
	value.floatValue = pfloatValue;
	in = pHandleIn;
	out = pHandleOut;
}

Keyframe::Keyframe(double pTime, double pDoubleValue, KeyframeHandle pHandleIn, KeyframeHandle pHandleOut)
{
	time = pTime;
	value.doubleValue = pDoubleValue;
	in = pHandleIn;
	out = pHandleOut;
}