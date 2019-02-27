#include "DopeSheet.h"
#include "Editor.h"

DopeSheet::DopeSheet(Editor *peditor)
{
	editor = peditor;
	animations.push_back(Animation((void *)keymebool, PropertyType::BOOL_VAL));
	animations[0].InsertKeyframe(Keyframe(0, false));
	animations[0].InsertKeyframe(Keyframe(1, true));
	animations[0].InsertKeyframe(Keyframe(2, false));
	animations[0].InsertKeyframe(Keyframe(3, true));
	animations[0].InsertKeyframe(Keyframe(4, false));
	animations[0].InsertKeyframe(Keyframe(5, true));
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

	ImGui::Checkbox("keymebool", &keymebool);

	ImGui::End();
}
