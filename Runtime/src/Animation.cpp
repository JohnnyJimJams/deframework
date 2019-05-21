#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(std::string p_id, void *p_property, KeyframePropertyType p_type)
{
	id = p_id;
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
				for (unsigned int i = 1; i < keyframes.size(); i++)
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
				for (unsigned int i = 1; i < keyframes.size(); i++)
				{
					// check if value falls between keyframes[i].time and keyframes[i+1]
					if (time < keyframes[i].time)
					{
						Keyframe *KA = &keyframes[i - 1];
						if (KA->interpolation == KeyframeInterpolationType::CONSTANT)
						{
							// Constant
							result = KA->value.intValue;
						}
						else
						{
							Keyframe *KB = &keyframes[i];
							double length = KB->time - KA->time;
							double t = (time - KA->time) / length;
							if (KA->interpolation == KeyframeInterpolationType::LINEAR)
							{
								// Linear
								int valueLength = KB->value.intValue - KA->value.intValue;
								result = (int)(KA->value.intValue + valueLength * t);
							}
							else
							{
								// Curved
								Keyframe *KZ, *KC;
								if (((int)i - 2) < 0)
									KZ = &keyframes[i - 1];
								else
									KZ = &keyframes[i - 2];

								if (i + 1 == keyframes.size())
									KC = &keyframes[i];
								else
									KC = &keyframes[i + 1];

								result = (int)(0.5f * ((2 * KA->value.intValue) + 
									(KB->value.intValue - KZ->value.intValue) * t + 
									(2 * KZ->value.intValue - 5 * KA->value.intValue + 4 * KB->value.intValue - KC->value.intValue) * t * t + 
									(3 * KA->value.intValue - KZ->value.intValue - 3 * KB->value.intValue + KC->value.intValue) * t * t * t));
							}
						}
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
				for (unsigned int i = 1; i < keyframes.size(); i++)
				{
					// check if value falls between keyframes[i].time and keyframes[i+1]
					if (time < keyframes[i].time)
					{
						Keyframe *KA = &keyframes[i - 1];
						if (KA->interpolation == KeyframeInterpolationType::CONSTANT)
						{
							// Constant
							result = KA->value.floatValue;
						}
						else
						{
							Keyframe *KB = &keyframes[i];
							double length = KB->time - KA->time;
							double t = (time - KA->time) / length;
							if (KA->interpolation == KeyframeInterpolationType::LINEAR)
							{
								// Linear
								float valueLength = KB->value.floatValue - KA->value.floatValue;
								result = (float)(KA->value.floatValue + valueLength * t);
							}
							else
							{
								// Curved
								Keyframe *KZ, *KC;
								if (((int)i - 2) == -1)
									KZ = &keyframes[i - 1];
								else
									KZ = &keyframes[i - 2];

								if (i + 1 == keyframes.size())
									KC = &keyframes[i];
								else
									KC = &keyframes[i + 1];

								result = (float)(0.5f * ((2.0f * KA->value.floatValue) + 
									(KB->value.floatValue - KZ->value.floatValue) * t + 
									(2.0f * KZ->value.floatValue - 5.0f * KA->value.floatValue + 4.0f * KB->value.floatValue - KC->value.floatValue) * t * t + 
									(3.0f * KA->value.floatValue - KZ->value.floatValue - 3.0f * KB->value.floatValue + KC->value.floatValue) * t * t * t));
							}

						}
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
				for (unsigned int i = 1; i < keyframes.size(); i++)
				{
					// check if value falls between keyframes[i].time and keyframes[i+1]
					if (time < keyframes[i].time)
					{
						Keyframe *KA = &keyframes[i - 1];
						if (KA->interpolation == KeyframeInterpolationType::CONSTANT)
						{
							// Constant
							result = KA->value.doubleValue;
						}
						else
						{
							Keyframe *KB = &keyframes[i];
							double length = KB->time - KA->time;
							double t = (time - KA->time) / length;
							if (KA->interpolation == KeyframeInterpolationType::LINEAR)
							{
								// Linear
								double valueLength = KB->value.doubleValue - KA->value.doubleValue;
								result = KA->value.doubleValue + valueLength * t;
							}
							else
							{
								// Curved
								Keyframe *KZ, *KC;
								if (((int)i - 2) == -1)
									KZ = &keyframes[i - 1];
								else
									KZ = &keyframes[i - 2];

								if ((i + 1) == keyframes.size())
									KC = &keyframes[i];
								else
									KC = &keyframes[i + 1];

								result = 0.5f * ((2 * KA->value.doubleValue) + 
									(KB->value.doubleValue - KZ->value.doubleValue) * t + 
									(2 * KZ->value.doubleValue - 5 * KA->value.doubleValue + 4 * KB->value.doubleValue - KC->value.doubleValue) * t * t + 
									(-KZ->value.doubleValue + 3 * KA->value.doubleValue - 3 * KB->value.doubleValue + KC->value.doubleValue) * t * t * t);
							}
						}
						break;
					}
				}
			}

	if (updateProperty) *(double *)property = result;
	return result;
}

glm::vec3 Animation::EvaluateVec3(double time, bool updateProperty)
{
	if (keyframes.size() == 0) return glm::vec3(); // no keyframes, bail without updating property, return value is a dummy value

	glm::vec3 result = glm::vec3();
	if (keyframes.size() == 1)
		result = keyframes[0].value.vec3Value; // Only one keyframe, just return it
	else
		if (keyframes[0].time >= time)
			result = keyframes[0].value.vec3Value; // evaluation time is before the first keyframe, return first keyframe
		else
			if (keyframes[keyframes.size() - 1].time <= time)
				result = keyframes[keyframes.size() - 1].value.vec3Value; // evaluation time is after the last keyframe, return last keyframe
			else
			{
				for (unsigned int i = 1; i < keyframes.size(); i++)
				{
					// check if value falls between keyframes[i].time and keyframes[i+1]
					if (time < keyframes[i].time)
					{
						Keyframe* KA = &keyframes[i - 1];
						if (KA->interpolation == KeyframeInterpolationType::CONSTANT)
						{
							// Constant
							result = KA->value.vec3Value;
						}
						else
						{
							Keyframe* KB = &keyframes[i];
							double length = KB->time - KA->time;
							float t = (time - KA->time) / length;
							if (KA->interpolation == KeyframeInterpolationType::LINEAR)
							{
								// Linear
								glm::vec3 valueLength = KB->value.vec3Value - KA->value.vec3Value;
								result = (glm::vec3)(KA->value.vec3Value + valueLength * t);
							}
							else
							{
								// Curved
								Keyframe* KZ, * KC;
								if (((int)i - 2) == -1)
									KZ = &keyframes[i - 1];
								else
									KZ = &keyframes[i - 2];

								if (i + 1 == keyframes.size())
									KC = &keyframes[i];
								else
									KC = &keyframes[i + 1];

								result = (glm::vec3)(0.5f * ((2.0f * KA->value.vec3Value) +
									(KB->value.vec3Value - KZ->value.vec3Value) * t +
									(2.0f * KZ->value.vec3Value - 5.0f * KA->value.vec3Value + 4.0f * KB->value.vec3Value - KC->value.vec3Value) * t * t +
									(3.0f * KA->value.vec3Value - KZ->value.vec3Value - 3.0f * KB->value.vec3Value + KC->value.vec3Value) * t * t * t));
							}

						}
						break;
					}
				}
			}

	if (updateProperty) * (glm::vec3*)property = result;
	return result;
}

glm::quat Animation::EvaluateQuat(double time, bool updateProperty)
{
	if (keyframes.size() == 0) return glm::quat(); // no keyframes, bail without updating property, return value is a dummy value

	glm::quat result = glm::quat();
	if (keyframes.size() == 1)
		result = keyframes[0].value.quatValue; // Only one keyframe, just return it
	else
		if (keyframes[0].time >= time)
			result = keyframes[0].value.quatValue; // evaluation time is before the first keyframe, return first keyframe
		else
			if (keyframes[keyframes.size() - 1].time <= time)
				result = keyframes[keyframes.size() - 1].value.quatValue; // evaluation time is after the last keyframe, return last keyframe
			else
			{
				for (unsigned int i = 1; i < keyframes.size(); i++)
				{
					// check if value falls between keyframes[i].time and keyframes[i+1]
					if (time < keyframes[i].time)
					{
						Keyframe* KA = &keyframes[i - 1];
						if (KA->interpolation == KeyframeInterpolationType::CONSTANT)
						{
							// Constant
							result = KA->value.quatValue;
						}
						else
						{
							Keyframe* KB = &keyframes[i];
							double length = KB->time - KA->time;
							float t = (time - KA->time) / length;
							if (KA->interpolation == KeyframeInterpolationType::LINEAR)
							{
								// Linear
								result = glm::slerp(KA->value.quatValue, KB->value.quatValue, t);
							}
							else
							{
								// Curved - Squad!
								Keyframe* KZ, * KC;
								if (((int)i - 2) == -1)
									KZ = &keyframes[i - 1];
								else
									KZ = &keyframes[i - 2];

								if (i + 1 == keyframes.size())
									KC = &keyframes[i];
								else
									KC = &keyframes[i + 1];

								/*
								result = (glm::quat)(0.5f * ((2.0f * KA->value.quatValue) +
									(KB->value.quatValue - KZ->value.quatValue) * t +
									(2.0f * KZ->value.quatValue - 5.0f * KA->value.quatValue + 4.0f * KB->value.quatValue - KC->value.quatValue) * t * t +
									(3.0f * KA->value.quatValue - KZ->value.quatValue - 3.0f * KB->value.quatValue + KC->value.quatValue) * t * t * t));

								*/
								// SQUAD!
								glm::quat s1 = glm::intermediate(KZ->value.quatValue, KA->value.quatValue, KB->value.quatValue);
								glm::quat s2 = glm::intermediate(KA->value.quatValue, KB->value.quatValue, KC->value.quatValue);
								result = glm::squad(KA->value.quatValue, KB->value.quatValue, s1, s2, t);
							}

						}
						break;
					}
				}
			}

	if (updateProperty) * (glm::quat*)property = result;
	return result;

}

int Animation::InsertKeyframe(Keyframe k)
{
	// keep this vector of Keyframes sorted by time
	if (keyframes.size() == 0) 
	{
		keyframes.push_back(k); // no keyframes, just add it
		return 1;
	}
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
	return 0;
}

void Animation::DeleteKeyframe(int index)
{
	keyframes.erase(keyframes.begin() + index);
}

std::vector<Keyframe> Animation::GetKeyframes()
{
	return keyframes;
}

KeyframePropertyType Animation::GetType()
{
	return type;
}

bool Animation::compareProperty(std::string prop)
{
	return prop == id;
}
