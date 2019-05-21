#include "Keyframe.h"

KeyframeHandle::KeyframeHandle()
{
	type = KeyframeHandleType::AUTO;
	position = glm::vec2(0, 0);
}

KeyframeHandle::KeyframeHandle(KeyframeHandleType pType, glm::vec2 pPosition)
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

Keyframe::Keyframe(double ptime, glm::vec3 pVec3Value, KeyframeInterpolationType pInterpolation, KeyframeHandle pHandleIn, KeyframeHandle pHandleOut)
{
	time = ptime;
	value.vec3Value = pVec3Value;
	interpolation = pInterpolation;
	in = pHandleIn;
	out = pHandleOut;
}

Keyframe::Keyframe(double ptime, glm::quat pQuatValue, KeyframeInterpolationType pInterpolation, KeyframeHandle pHandleIn, KeyframeHandle pHandleOut)
{
	time = ptime;
	value.quatValue = pQuatValue;
	interpolation = pInterpolation;
	in = pHandleIn;
	out = pHandleOut;
}
