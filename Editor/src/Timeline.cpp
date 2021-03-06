#include "Timeline.h"
#include "Editor.h"

Timeline::Timeline(Editor *peditor)
{
	editor = peditor;
}

Timeline::~Timeline()
{
}

void Timeline::DrawBar()
{
}

void Timeline::TickUI(bool* p_open)
{
	if (!ImGui::Begin("Timeline", p_open))
	{
		ImGui::End();
		return;
	}
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec4 col = ImVec4(0.1f, 0.2f, 0.1f, 0.7f);
	const ImU32 col32 = ImColor(col);
	const ImVec2 p = ImGui::GetCursorScreenPos();
	const ImVec2 s = ImGui::GetWindowSize();
	const ImVec2 s1 = ImGui::GetWindowContentRegionMax();
	
	int left = (int)p.x + 5;
	int right = (int)p.x + (int)s.x - 20;
	int ycentre = (int)(((p.y + s.y - 40) - (p.y + 5)) * 0.5) + (int)p.y + 5;
	draw_list->AddRectFilled(ImVec2((float)left, (float)ycentre - 5.0f), ImVec2((float)right, (float)ycentre + 5.0f), col32);
	double pos = editor->GetMusicSecondsNow() / editor->GetMusicSecondsTotal();
	draw_list->AddCircleFilled(ImVec2((float)left + ((float)right - (float)left) * (float)pos, (float)ycentre), 10, IM_COL32_WHITE);

	// Scrub time line on mouse down
	ImVec2 canvas_size = ImGui::GetContentRegionAvail();
	ImGui::InvisibleButton("timelinecanvas", canvas_size);	// allows for clicking, hovering without moving the window
	if (ImGui::IsItemHovered())
	{ 
		if (ImGui::IsMouseDown(0))
		{
			ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
			ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);

			float mousex01 = (ImGui::GetIO().MousePos.x - canvas_pos.x) / (float)(right - left);
			editor->SetMusicSeconds(editor->GetMusicSecondsTotal() * mousex01);
			editor->GetDemo()->Tick(editor->GetMusicSecondsNow());
			//editor->GetConsole()->Log("set music time: %f\n", pos);
		}
	}

	ImGui::End();
}
