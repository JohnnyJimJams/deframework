#include "DemoView.h"
#include "Editor.h"
#include "Texture2D.h"

DemoView::DemoView(Editor *peditor)
{
	editor = peditor;

	m_texture = new Texture2D("C:\\Users\\Alienware\\Desktop\\Demoscene\\deframework2_demoExample\\smiley.jpg");
}

DemoView::~DemoView()
{
	delete m_texture;
	delete m_shader;
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
	//draw_list->AddCallback()

	//ImGui::InvisibleButton("demoviewcanvas", windowSize);	// allows for clicking, hovering without moving the window

	ImGui::Image((ImTextureID)m_texture->GetId(), windowSize);

	ImGui::End();
}