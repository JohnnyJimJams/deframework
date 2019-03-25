#include "Assets.h"
#include "Editor.h"
#include <windows.h>
#include <Commdlg.h>

static OPENFILENAME ofn;

static char szFile[100];

Assets::Assets(Editor *peditor)
{
	editor = peditor;
}

Assets::~Assets()
{
}

void Assets::TickUI(bool* p_open)
{
	if (!ImGui::Begin("Assets", p_open))
	{
		ImGui::End();
		return;
	}

	// Assets buttons
	if (ImGui::Button("Add Asset"))
	{
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_ALLOWMULTISELECT;
		GetOpenFileName(&ofn);

		// Now simpley display the file name 
		MessageBox(NULL, ofn.lpstrFile, "File Name", MB_OK);
	}
	ImGui::SameLine();
	if (ImGui::Button("Remove Asset/s"))
	{
		if (!m_selectedMeshes.empty() && !m_selectedTextures.empty() && !m_selectedShaders.empty() && !m_selectedMaterials.empty())
		{ 
			// modal are you sure?
			ImGui::OpenPopup("Remove Assets from demo? This doesn't delete any files on disk.");
		}
	}

	if (ImGui::BeginPopupModal("Remove Assets?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("This will remote all selected assets from the demo... no files will be deleted.\nAre you sure?!\n\n");
		ImGui::Separator();

		if (ImGui::Button("Remove", ImVec2(120, 0))) { 
			if (!m_selectedMeshes.empty()) 
			{
				editor->GetDemo()->RemoveMeshes(m_selectedMeshes);
				m_selectedMeshes.clear();
			}
			ImGui::CloseCurrentPopup(); 
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		ImGui::EndPopup();
	}

	//// List of layers as trees
	//auto layers = editor->GetDemo()->GetLayers();
	//int node_clicked = -1;
	//int i = 0;
	//for (auto layer : layers)
	//{
	//	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
	//	if (std::find(m_selectedLayers.begin(), m_selectedLayers.end(), layer) != m_selectedLayers.end())
	//	{
	//		node_flags = node_flags | ImGuiTreeNodeFlags_Selected;
	//	}
	//	
	//	bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, layer->name.c_str(), i);
	//	if (node_open)
	//	{
	//		ImGui::Text(layer->name.c_str());
	//		ImGui::TreePop();
	//	}

	//	if (ImGui::IsItemClicked())
	//		node_clicked = i;

	//	i++;
	//}
	//if (node_clicked != -1)
	//{
	//	// Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
	//	if (ImGui::GetIO().KeyCtrl)
	//		m_selectedLayers.push_back(layers[node_clicked]);
	//	else
	//	{
	//		m_selectedLayers.clear();
	//		m_selectedLayers.push_back(layers[node_clicked]);
	//	}
	//}

	ImGui::End();
}
