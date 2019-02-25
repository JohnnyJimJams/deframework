#include "Toolbar.h"
#include "Editor.h"

Toolbar::Toolbar(Editor *peditor)
{
	editor = peditor;
}

Toolbar::~Toolbar()
{
}

void Toolbar::TickUI(bool* p_open)
{
	ImGui::SetNextWindowPos(ImVec2(15, 15), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(80, 100), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Toolbar", p_open))
	{
		ImGui::End();
		return;
	}
	if (ImGui::Button("Play"))
	{
		editor->Play();
	}
	if (ImGui::Button("Stop"))
	{
		editor->Stop();
	}
	ImGui::End();
}
