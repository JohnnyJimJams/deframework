#include "CurveEditor.h"
#include "Editor.h"

CurveEditor::CurveEditor(Editor *peditor)
{
	editor = peditor;
}

CurveEditor::~CurveEditor()
{
}

void CurveEditor::TickUI(bool* p_open)
{
	if (!ImGui::Begin("Curve Editor", p_open))
	{
		ImGui::End();
		return;
	}
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec4 col = ImVec4(0.1f, 0.2f, 0.1f, 0.7f);
	const ImU32 col32 = ImColor(col);
	const ImVec2 p = ImGui::GetCursorScreenPos();
	const ImVec2 s = ImGui::GetWindowSize();
	
	int left = (int)p.x + 5;
	int right = (int)p.x + (int)s.x - 20;
	int ycentre = (int)((((int)p.y + (int)s.y - 40) - ((int)p.y + 5)) * 0.5) + (int)p.y + 5;
	
	// horizontal line
	draw_list->AddRectFilled(ImVec2((float)left, (float)ycentre), ImVec2((float)right, (float)ycentre + 1.0f), col32);

	ImVec2 canvas_size = ImGui::GetContentRegionAvail();
	ImGui::InvisibleButton("curveeditorcanvas", canvas_size);	// allows for clicking, hovering without moving the window

	if (animation)
	{
		for (int x = left + 1; x <= right; x++)
		{
			double time1 = (x - left - 1) / ((double)(right - left)) * editor->GetMusicSecondsTotal();
			double time2 = (x - left) / ((double)(right - left)) * editor->GetMusicSecondsTotal();
			double y1 = animation->EvaluateDouble(time1, false);
			double y2 = animation->EvaluateDouble(time2, false);
			draw_list->AddLine(ImVec2(x - 1.0f, (float)y1 + (float)ycentre), ImVec2((float)x, (float)y2 + (float)ycentre), IM_COL32_WHITE);
		}
	}

	ImGui::End();
}
