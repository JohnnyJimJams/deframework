#include "Animation.h"

Animation::Animation(void *p_property, PropertyType p_type)
{
	property = p_property;
	type = p_type;
}

bool Animation::EvaluateBool(double time, bool updateProperty)
{
	if (keyframes.size() == 0) return false; // no keyframes, bail without updating property, return value is a dummy value

	bool result = false;
	if (keyframes.size() == 1)  // Only one keyframe, just return it
		result = keyframes[0].value.boolValue;
	else 
		if (keyframes[0].time >= time) 
			result = keyframes[0].value.boolValue; // evaluation time is before the first keyframe, return first keyframe
		else 
			if (keyframes[keyframes.size() - 1].time <= time) 
				result = keyframes[keyframes.size() - 1].value.boolValue; // evaluation time is after the last keyframe, return last keyframe
			else
			{
				for (int i = 1; i < keyframes.size(); i++)
				{
					// check if value falls between keyframes[i].time and keyframes[i+1]
					if (time < keyframes[i].time)
					{
						result = keyframes[i - 1].value.boolValue;
						goto ExitLoop;
					}
				}
			}
	ExitLoop:
	if (updateProperty) *(bool *)property = result;
	return result;
}

int Animation::EvaluateInt(double time, bool updateProperty)
{
	if (keyframes.size() == 0) return 0; // no keyframes, bail without updating property, return value is a dummy value

	int result = false;
	if (keyframes.size() == 1)
		result = keyframes[0].value.intValue; // Only one keyframe, just return it
	else
		if (keyframes[0].time >= time)
			result = keyframes[0].value.intValue; // evaluation time is before the first keyframe, return first keyframe
		else
			if (keyframes[keyframes.size() - 1].time <= time)
				result = keyframes[keyframes.size() - 1].value.intValue; // evaluation time is after the last keyframe, return last keyframe
			else
			{
				for (int i = 1; i < keyframes.size(); i++)
				{
					// check if value falls between keyframes[i].time and keyframes[i+1]
					if (time < keyframes[i].time)
					{
						result = keyframes[i - 1].value.intValue;
						break;
					}
				}
			}

	if (updateProperty) *(int *)property = result;
	return result;
}

float Animation::EvaluateFloat(double time, bool updateProperty)
{
	if (keyframes.size() == 0) return 0.0f; // no keyframes, bail without updating property, return value is a dummy value

	float result = false;
	if (keyframes.size() == 1)
		result = keyframes[0].value.floatValue; // Only one keyframe, just return it
	else
		if (keyframes[0].time >= time)
			result = keyframes[0].value.floatValue; // evaluation time is before the first keyframe, return first keyframe
		else
			if (keyframes[keyframes.size() - 1].time <= time)
				result = keyframes[keyframes.size() - 1].value.floatValue; // evaluation time is after the last keyframe, return last keyframe
			else
			{
				for (int i = 1; i < keyframes.size(); i++)
				{
					// check if value falls between keyframes[i].time and keyframes[i+1]
					if (time < keyframes[i].time)
					{
						//Keyframe *KA = &keyframes[i - 1];
						//Keyframe *KB = &keyframes[i];
						result = keyframes[i - 1].value.floatValue; // TODO use handles to interpolate between this and the next keyframe
						break;
					}
				}
			}

	if (updateProperty) *(float *)property = result;
	return result;
}

double Animation::EvaluateDouble(double time, bool updateProperty)
{
	if (keyframes.size() == 0) return 0.0f; // no keyframes, bail without updating property, return value is a dummy value

	double result = false;
	if (keyframes.size() == 1)
		result = keyframes[0].value.doubleValue; // Only one keyframe, just return it
	else
		if (keyframes[0].time >= time)
			result = keyframes[0].value.doubleValue; // evaluation time is before the first keyframe, return first keyframe
		else
			if (keyframes[keyframes.size() - 1].time <= time)
				result = keyframes[keyframes.size() - 1].value.doubleValue; // evaluation time is after the last keyframe, return last keyframe
			else
			{
				for (int i = 1; i < keyframes.size(); i++)
				{
					// check if value falls between keyframes[i].time and keyframes[i+1]
					if (time < keyframes[i].time)
					{
						//Keyframe *KA = &keyframes[i - 1];
						//Keyframe *KB = &keyframes[i];
						result = keyframes[i - 1].value.doubleValue; // TODO use handles to interpolate between this and the next keyframe
						break;
					}
				}
			}

	if (updateProperty) *(float *)property = result;
	return result;
}

int Animation::InsertKeyframe(Keyframe k)
{
	// keep this vector of Keyframes sorted by time
	if (keyframes.size() == 0) return 0.0f; // no keyframes, bail without updating property, return value is a dummy value

	if (keyframes[0].time >= k.time)
	{
		std::vector<Keyframe>::iterator it = keyframes.begin();
		keyframes.insert(it, k); // keyframe to insert is before the first keyframe, put it up front
	}
	else
		if (keyframes[keyframes.size() - 1].time <= k.time)
		{
			keyframes.push_back(k); // keyframe to insert is after the last keyframe, put it at the back
		}
		else
		{
			for (std::vector<Keyframe>::iterator it = keyframes.begin() + 1; it != keyframes.end(); ++it)
			{
				// check if value falls between keyframes[i].time and keyframes[i+1]
				if (k.time < it->time)
				{
					keyframes.insert(it, k);
					break;
				}
			}
		}
}

void Animation::DeleteKeyframe(int index)
{
	keyframes.erase(keyframes.begin() + index);
}
