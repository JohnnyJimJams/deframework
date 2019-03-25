#include "DopeSheet.h"
#include "Editor.h"

using namespace std;

DopeSheet::DopeSheet(Editor *peditor)
{
	editor = peditor;

	// Test bool keyframes
	animations.push_back(Animation((void *)&keymebool, KeyframePropertyType::BOOL_VAL));
	animations[0].InsertKeyframe(Keyframe(0, false, KeyframeInterpolationType::CONSTANT));
	animations[0].InsertKeyframe(Keyframe(1, true, KeyframeInterpolationType::CONSTANT));
	animations[0].InsertKeyframe(Keyframe(2, false, KeyframeInterpolationType::CONSTANT));
	animations[0].InsertKeyframe(Keyframe(3, true, KeyframeInterpolationType::CONSTANT));
	animations[0].InsertKeyframe(Keyframe(4, false, KeyframeInterpolationType::CONSTANT));
	animations[0].InsertKeyframe(Keyframe(5, true, KeyframeInterpolationType::CONSTANT));
	//editor->GetConsole()->Log("Dump of keyframes - Bool\n");
	std::vector<Keyframe> kf = animations[0].GetKeyframes();
	//editor->GetConsole()->Log("num keyframes: %d\n", kf.size());
	//for (unsigned int i = 0; i < kf.size(); i++)
	//{
	//	editor->GetConsole()->Log("time: %f  value: %d\n", kf[i].time, kf[i].value.boolValue);
	//}

	// Test int keyframes
	animations.push_back(Animation((void *)&keymeint, KeyframePropertyType::INT_VAL));
	animations[1].InsertKeyframe(Keyframe(0, 3, KeyframeInterpolationType::CURVED));
	animations[1].InsertKeyframe(Keyframe(1, 1, KeyframeInterpolationType::CURVED));
	animations[1].InsertKeyframe(Keyframe(2, 4, KeyframeInterpolationType::CURVED));
	animations[1].InsertKeyframe(Keyframe(3, 1, KeyframeInterpolationType::CURVED));
	animations[1].InsertKeyframe(Keyframe(4, 5, KeyframeInterpolationType::CURVED));
	animations[1].InsertKeyframe(Keyframe(5, 9, KeyframeInterpolationType::CURVED));
	//editor->GetConsole()->Log("Dump of keyframes - Int\n");
	kf = animations[1].GetKeyframes();
	//editor->GetConsole()->Log("num keyframes: %d\n", kf.size());
	//for (unsigned int i = 0; i < kf.size(); i++)
	//{
	//	editor->GetConsole()->Log("time: %f  value: %d\n", kf[i].time, kf[i].value.intValue);
	//}

	// Test float keyframes
	animations.push_back(Animation((void *)&keymefloat, KeyframePropertyType::FLOAT_VAL));
	animations[2].InsertKeyframe(Keyframe(0.0, -10.0f, KeyframeInterpolationType::CURVED, KeyframeHandle(), KeyframeHandle()));
	animations[2].InsertKeyframe(Keyframe(10.0, 10.0f, KeyframeInterpolationType::CURVED, KeyframeHandle(), KeyframeHandle()));

	//editor->GetConsole()->Log("Dump of keyframes - float\n");
	kf = animations[2].GetKeyframes();
	//editor->GetConsole()->Log("num keyframes: %d\n", kf.size());
	//for (unsigned int i = 0; i < kf.size(); i++)
	//{
	//	editor->GetConsole()->Log("time: %f  value: %f\n", kf[i].time, kf[i].value.floatValue);
	//}

	// Test double keyframes
	animations.push_back(Animation((void *)&keymedouble, KeyframePropertyType::DOUBLE_VAL));
	animations[3].InsertKeyframe(Keyframe(0.0, 0.3, KeyframeInterpolationType::CURVED, KeyframeHandle(), KeyframeHandle()));
	animations[3].InsertKeyframe(Keyframe(15.0, -150.2, KeyframeInterpolationType::CURVED, KeyframeHandle(), KeyframeHandle()));
	animations[3].InsertKeyframe(Keyframe(30.0, 150.0, KeyframeInterpolationType::CURVED, KeyframeHandle(), KeyframeHandle()));
	animations[3].InsertKeyframe(Keyframe(45.0, 130.0, KeyframeInterpolationType::CURVED, KeyframeHandle(), KeyframeHandle()));
	animations[3].InsertKeyframe(Keyframe(60.0, -30.0, KeyframeInterpolationType::CURVED, KeyframeHandle(), KeyframeHandle()));
	animations[3].InsertKeyframe(Keyframe(75.0, 30.0, KeyframeInterpolationType::CURVED, KeyframeHandle(), KeyframeHandle()));
	animations[3].InsertKeyframe(Keyframe(90.0, -30.0, KeyframeInterpolationType::CURVED, KeyframeHandle(), KeyframeHandle()));
	animations[3].InsertKeyframe(Keyframe(105.0, 30.0, KeyframeInterpolationType::CURVED, KeyframeHandle(), KeyframeHandle()));
	animations[3].InsertKeyframe(Keyframe(120.0, -30.0, KeyframeInterpolationType::CURVED, KeyframeHandle(), KeyframeHandle()));
	animations[3].InsertKeyframe(Keyframe(135.0, 30.0, KeyframeInterpolationType::CURVED, KeyframeHandle(), KeyframeHandle()));
	animations[3].InsertKeyframe(Keyframe(150.0, -30.0, KeyframeInterpolationType::CURVED, KeyframeHandle(), KeyframeHandle()));
	animations[3].InsertKeyframe(Keyframe(205.0, 80.0, KeyframeInterpolationType::CURVED, KeyframeHandle(), KeyframeHandle()));
	//editor->GetConsole()->Log("Dump of keyframes - Double\n");
	kf = animations[3].GetKeyframes();
	//editor->GetConsole()->Log("num keyframes: %\n", kf.size());
	//for (unsigned int i = 0; i < kf.size(); i++)
	//{
	//	editor->GetConsole()->Log("time: %f  value: %f\n", kf[i].time, kf[i].value.doubleValue);
	//}

	// set curve 3 to draw in the curve editor
	editor->GetCurveEditor()->animation = &animations[3];

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

	// Dopesheet buttons
	if (ImGui::Button("Add Layer"))
	{
		editor->GetDemo()->AddLayer();
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete Layer/s"))
	{
		if (!m_selectedLayers.empty())
		{ 
			// modal are you sure?
			ImGui::OpenPopup("Delete Layers?");
		}
	}
	ImGui::SameLine();
	if (ImGui::ArrowButton("##up", ImGuiDir_Up)) 
	{
		if (m_selectedLayers.size() == 1)
		{
			string nameSelected = m_selectedLayers[0]->name;
			int index = editor->GetDemo()->GetLayerIndex(nameSelected);
			if (index > 0) // -1 means not found, 0 is already at the top
			{
				vector<Layer *> &layers = editor->GetDemo()->GetLayers();
				swap(layers[index], layers[index - 1]);
			}
		}
	}
	ImGui::SameLine();
	if (ImGui::ArrowButton("##down", ImGuiDir_Down)) 
	{ 
		if (m_selectedLayers.size() == 1)
		{
			string nameSelected = m_selectedLayers[0]->name;
			int index = editor->GetDemo()->GetLayerIndex(nameSelected);
			vector<Layer *> &layers = editor->GetDemo()->GetLayers();
			if (index > -1) // -1 means not found, layers.size()-1 is already at the bottom
			{
				if (index < ((int)layers.size() - 1))
				{
					swap(layers[index], layers[index + 1]);
				}
			}
		}
	}

	if (ImGui::BeginPopupModal("Delete Layers?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("This will delete all selected layers and their children.\nAre you sure?!\n\n");
		ImGui::Separator();

		if (ImGui::Button("Delete", ImVec2(120, 0))) { 
			editor->GetDemo()->DeleteLayers(&m_selectedLayers);
			m_selectedLayers.clear();
			ImGui::CloseCurrentPopup(); 
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		ImGui::EndPopup();
	}

	// List of layers as trees
	auto layers = editor->GetDemo()->GetLayers();
	int node_clicked = -1;
	int i = 0;
	for (auto layer : layers)
	{
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		if (std::find(m_selectedLayers.begin(), m_selectedLayers.end(), layer) != m_selectedLayers.end())
		{
			node_flags = node_flags | ImGuiTreeNodeFlags_Selected;
		}
		
		bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, layer->name.c_str(), i);
		if (node_open)
		{
			ImGui::Text(layer->name.c_str());
			ImGui::TreePop();
		}

		if (ImGui::IsItemClicked())
			node_clicked = i;

		i++;
	}
	if (node_clicked != -1)
	{
		// Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
		if (ImGui::GetIO().KeyCtrl)
			m_selectedLayers.push_back(layers[node_clicked]);
		else
		{
			m_selectedLayers.clear();
			m_selectedLayers.push_back(layers[node_clicked]);
		}
	}
	//animations[0].EvaluateBool(editor->GetMusicSecondsNow());
	//animations[1].EvaluateInt(editor->GetMusicSecondsNow());
	//animations[2].EvaluateFloat(editor->GetMusicSecondsNow());
	//animations[3].EvaluateDouble(editor->GetMusicSecondsNow());

	//ImGui::Checkbox("keymebool", &keymebool);
	//ImGui::SliderInt("keymeint", &keymeint, 0, 10);
	//ImGui::SliderFloat("keymefloat", &keymefloat, -100.0f, 100.0f);
	//float dbl2flt = (float)keymedouble;
	//ImGui::SliderFloat("keymedouble", &dbl2flt, -100.0f, 100.0f);

	ImGui::End();
}

void DopeSheet::Init()
{
}
