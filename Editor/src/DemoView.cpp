#include "DemoView.h"

DemoView::DemoView(Editor *peditor)
{
	editor = peditor;
}

DemoView::~DemoView()
{
}

void DemoView::TickUI(bool* p_open)
{
	if (!ImGui::Begin("Demo View", p_open))
	{
		ImGui::End();
		return;
	}
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec4 backGroundCol = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	const ImU32 col32 = ImColor(backGroundCol);
	ImVec2 windowPos = ImGui::GetCursorScreenPos();
	ImVec2 windowSize = ImGui::GetContentRegionAvail();
	
	// Draw background colour
	draw_list->AddRectFilled(windowPos, ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y), col32);

	//ImGui::InvisibleButton("demoviewcanvas", windowSize);	// allows for clicking, hovering without moving the window

	ImGui::End();
}
