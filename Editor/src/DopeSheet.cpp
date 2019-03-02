#include "DopeSheet.h"
#include "Editor.h"

DopeSheet::DopeSheet(Editor *peditor)
{
	editor = peditor;

	// Test bool keyframes
	animations.push_back(Animation((void *)&keymebool, PropertyType::BOOL_VAL));
	animations[0].InsertKeyframe(Keyframe(0, false));
	animations[0].InsertKeyframe(Keyframe(1, true));
	animations[0].InsertKeyframe(Keyframe(2, false));
	animations[0].InsertKeyframe(Keyframe(3, true));
	animations[0].InsertKeyframe(Keyframe(4, false));
	animations[0].InsertKeyframe(Keyframe(5, true));
	editor->GetConsole()->Log("Dump of keyframes - Bool\n");
	std::vector<Keyframe> kf = animations[0].GetKeyframes();
	editor->GetConsole()->Log("num keyframes: %d\n", kf.size());
	for (int i = 0; i < kf.size(); i++)
	{
		editor->GetConsole()->Log("time: %f  value: %d\n", kf[i].time, kf[i].value.boolValue);
	}

	// Test int keyframes
	animations.push_back(Animation((void *)&keymeint, PropertyType::INT_VAL));
	animations[1].InsertKeyframe(Keyframe(0, 3));
	animations[1].InsertKeyframe(Keyframe(1, 1));
	animations[1].InsertKeyframe(Keyframe(2, 4));
	animations[1].InsertKeyframe(Keyframe(3, 1));
	animations[1].InsertKeyframe(Keyframe(4, 5));
	animations[1].InsertKeyframe(Keyframe(5, 9));
	editor->GetConsole()->Log("Dump of keyframes - Int\n");
	kf = animations[1].GetKeyframes();
	editor->GetConsole()->Log("num keyframes: %d\n", kf.size());
	for (int i = 0; i < kf.size(); i++)
	{
		editor->GetConsole()->Log("time: %f  value: %d\n", kf[i].time, kf[i].value.intValue);
	}

	// Test float keyframes
	animations.push_back(Animation((void *)&keymefloat, PropertyType::FLOAT_VAL));
	animations[2].InsertKeyframe(Keyframe(0.0, 10.0f, KeyframeHandle(KeyframeHandleType::Smooth, Eigen::Vector2f(0, 0)), KeyframeHandle(KeyframeHandleType::Smooth, Eigen::Vector2f(0, 0))));
	animations[2].InsertKeyframe(Keyframe(2.0, 5.0f, KeyframeHandle(KeyframeHandleType::Smooth, Eigen::Vector2f(0, 0)), KeyframeHandle(KeyframeHandleType::Smooth, Eigen::Vector2f(0, 0))));
	animations[2].InsertKeyframe(Keyframe(5.0, 1.0f, KeyframeHandle(KeyframeHandleType::Smooth, Eigen::Vector2f(0, 0)), KeyframeHandle(KeyframeHandleType::Smooth, Eigen::Vector2f(0, 0))));

	editor->GetConsole()->Log("Dump of keyframes - float\n");
	kf = animations[2].GetKeyframes();
	editor->GetConsole()->Log("num keyframes: %d\n", kf.size());
	for (int i = 0; i < kf.size(); i++)
	{
		editor->GetConsole()->Log("time: %f  value: %f\n", kf[i].time, kf[i].value.floatValue);
	}

	// Test double keyframes
	animations.push_back(Animation((void *)&keymedouble, PropertyType::DOUBLE_VAL));
	animations[3].InsertKeyframe(Keyframe(0.0, 4.3, KeyframeHandle(KeyframeHandleType::Smooth, Eigen::Vector2f(0, 0)), KeyframeHandle(KeyframeHandleType::Smooth, Eigen::Vector2f(0, 0))));
	animations[3].InsertKeyframe(Keyframe(3.0, 4.2, KeyframeHandle(KeyframeHandleType::Smooth, Eigen::Vector2f(0, 0)), KeyframeHandle(KeyframeHandleType::Smooth, Eigen::Vector2f(0, 0))));
	animations[3].InsertKeyframe(Keyframe(6.0, 4.1, KeyframeHandle(KeyframeHandleType::Smooth, Eigen::Vector2f(0, 0)), KeyframeHandle(KeyframeHandleType::Smooth, Eigen::Vector2f(0, 0))));
	editor->GetConsole()->Log("Dump of keyframes - Double\n");
	kf = animations[3].GetKeyframes();
	editor->GetConsole()->Log("num keyframes: %\n", kf.size());
	for (int i = 0; i < kf.size(); i++)
	{
		editor->GetConsole()->Log("time: %f  value: %f\n", kf[i].time, kf[i].value.doubleValue);
	}

}

DopeSheet::~DopeSheet()
{
}

void DopeSheet::TickUI(bool* p_open)
{
	if (!ImGui::Begin("DopeSheet", p_open))
	{
		ImGui::End();
		return;
	}

	animations[0].EvaluateBool(editor->GetMusicSecondsNow());
	animations[1].EvaluateInt(editor->GetMusicSecondsNow());
	animations[2].EvaluateFloat(editor->GetMusicSecondsNow());
	animations[3].EvaluateDouble(editor->GetMusicSecondsNow());

	ImGui::Checkbox("keymebool", &keymebool);
	ImGui::SliderInt("keymeint", &keymeint, 0, 10);
	ImGui::SliderFloat("keymefloat", &keymefloat, -100.0f, 100.0f);
	float dbl2flt = keymedouble;
	ImGui::SliderFloat("keymedouble", &dbl2flt, -100.0f, 100.0f);

	ImGui::End();
}

void DopeSheet::Init()
{
}
