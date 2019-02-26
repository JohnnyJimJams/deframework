#include "Keyframe.h"

Keyframe::Keyframe()
{
}

KeyframeHandle::KeyframeHandle()
{
	type = KeyframeHandleType::None;
	position = Eigen::Vector2f(0, 0);
}
