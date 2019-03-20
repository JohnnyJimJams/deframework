#include "PropertyEditor.h"
#include "Editor.h"

PropertyEditor::PropertyEditor(Editor *peditor)
{
	editor = peditor;
	m_entity = nullptr;
}

PropertyEditor::~PropertyEditor()
{
}

void PropertyEditor::TickUI(bool* p_open)
{
	//ImGui::SetNextWindowPos(ImVec2(15, 15), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(80, 100), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Properties", p_open))
	{
		ImGui::End();
		return;
	}

	if (m_entity)
	{
		ImGui::InputText("Name", (char *)m_entity->Name.c_str(), m_entity->Name.capacity() + 1);
		//m_entity->Name = name;
		ImGui::Checkbox("Active", &m_entity->Active);
		ImGui::SliderFloat3("Position", (float*)&m_entity->Position, -10.0f, 10.0f);
		glm::vec3 euler = degrees(m_entity->GetEulerAngles());
		ImGui::SliderFloat3("Rotation", (float *)&euler, -179.999f, 179.999f);
		m_entity->SetEulerAngles(radians(euler));
		ImGui::SliderFloat3("Scale", (float*)&m_entity->Scale, -10.0f, 10.0f);
	}

	ImGui::End();
}

void PropertyEditor::SetEntity(Entity * entity)
{
	m_entity = entity;
}

void PropertyEditor::ClearEntity()
{
	m_entity = nullptr;
}
