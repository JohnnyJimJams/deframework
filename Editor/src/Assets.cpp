#include "Assets.h"
#include "Editor.h"
#include <windows.h>
#include <Commdlg.h>

static OPENFILENAME ofn;

static char szFile[1024];

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
	if (ImGui::Button("Create.."))
	{
		ImGui::OpenPopup("asset_create_popup");
	}
	ImGui::SameLine();
	if (ImGui::BeginPopup("asset_create_popup"))
	{
		if (ImGui::MenuItem("Material"))
		{
			std::string newMat = editor->GetDemo()->AddMaterial();
		}
		if (ImGui::MenuItem("Texture2D"))
		{
			std::string newTex = editor->GetDemo()->AddTexture2D();
		}
		if (ImGui::MenuItem("Mesh"))
		{
			std::string newMesh = editor->GetDemo()->AddMesh();
		}
		ImGui::EndPopup();
	}
	if (ImGui::Button("Load Asset/s"))
	{
		ZeroMemory(szFile, 1024);
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
		// Get results ()
		if (ofn.lpstrFile[0] != '\0')
		{
			std::string first = ofn.lpstrFile;
			char c = ofn.lpstrFile[first.size() + 1];
			if (c == '\0')
			{
				// single file selected
				LoadAsset(first);
			} 
			else
			{
				// multiple files selected
				std::string path = first;
				int currentPos = path.size() + 1;
				do
				{
					std::string current = &ofn.lpstrFile[currentPos];
					LoadAsset(path + "\\" + current);
					currentPos += current.size() + 1;
				} while (ofn.lpstrFile[currentPos] != '\0');
			}
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Remove Asset/s"))
	{
		if (!m_selectedMeshes.empty() || !m_selectedTextures.empty() || !m_selectedShaders.empty() || !m_selectedMaterials.empty())
		{ 
			// modal are you sure?
			ImGui::OpenPopup("Remove Assets?");
		}
	}

	if (ImGui::BeginPopupModal("Remove Assets?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("This will remote all selected assets from the demo... no files will be deleted.\nAre you sure?!\n\n");
		ImGui::Separator();

		if (ImGui::Button("Remove", ImVec2(120, 0))) { 
			if (!m_selectedMeshes.empty()) 
			{
				for (auto m : m_selectedMeshes)
					editor->GetDemo()->RemoveMesh(m);
				m_selectedMeshes.clear();
			}
			if (!m_selectedTextures.empty())
			{
				for (auto t : m_selectedTextures)
					editor->GetDemo()->RemoveTexture2D(t);
				m_selectedTextures.clear();
			}
			if (!m_selectedMaterials.empty())
			{
				for (auto m : m_selectedMaterials)
					editor->GetDemo()->RemoveMaterial(m);
				m_selectedMaterials.clear();
			}
			if (!m_selectedShaders.empty())
			{
				for (auto s : m_selectedShaders)
					editor->GetDemo()->RemoveShader(s);
				m_selectedShaders.clear();
			}
			editor->GetPropertyEditor()->ClearAll();
			ImGui::CloseCurrentPopup(); 
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
		ImGui::EndPopup();
	}

	std::string nodeClicked = "";
	std::string category = "";
	if (ImGui::CollapsingHeader("Materials"))
	{
		auto materials = editor->GetDemo()->GetMaterials();
		for (auto m : materials)
		{
			bool selected = std::find(m_selectedMaterials.begin(), m_selectedMaterials.end(), m.first) != m_selectedMaterials.end();
			if (ImGui::Selectable(m.first.c_str(), selected))
			{
				nodeClicked = m.first;
				category = "Materials";
			}
		}
	}

	if (ImGui::CollapsingHeader("Meshes"))
	{
		auto meshes = editor->GetDemo()->GetMeshes();
		for (auto m : meshes)
		{
			bool selected = std::find(m_selectedMeshes.begin(), m_selectedMeshes.end(), m.first) != m_selectedMeshes.end();
			if (ImGui::Selectable(m.first.c_str(), selected))
			{
				nodeClicked = m.first;
				category = "Meshes";
			}
		}
	}

	if (ImGui::CollapsingHeader("Textures"))
	{
		auto textures = editor->GetDemo()->GetTextures();
		for (auto t : textures)
		{
			bool selected = std::find(m_selectedTextures.begin(), m_selectedTextures.end(), t.first) != m_selectedTextures.end();
			if (ImGui::Selectable(t.first.c_str(), selected))
			{
				nodeClicked = t.first;
				category = "Textures";
			}
		}
	}

	if (ImGui::CollapsingHeader("Shaders"))
	{
		auto shaders = editor->GetDemo()->GetShaders();
		for (auto s : shaders)
		{
			bool selected = std::find(m_selectedShaders.begin(), m_selectedShaders.end(), s.first) != m_selectedShaders.end();
			if (ImGui::Selectable(s.first.c_str(), selected))
			{
				nodeClicked = s.first;
				category = "Shaders";
			}
		}
	}
	if (nodeClicked != "")
	{
		if (!ImGui::GetIO().KeyCtrl)
		{
			m_selectedMaterials.clear();
			m_selectedMeshes.clear();
			m_selectedShaders.clear();
			m_selectedTextures.clear();
			editor->GetPropertyEditor()->ClearAll();
		}
		if (category == "Materials")
		{
			m_selectedMaterials.push_back(nodeClicked);
			editor->GetPropertyEditor()->AddMaterial(editor->GetDemo()->GetMaterials()[nodeClicked]);
		}
		if (category == "Meshes")
		{
			m_selectedMeshes.push_back(nodeClicked);
			editor->GetPropertyEditor()->AddMesh(editor->GetDemo()->GetMeshes()[nodeClicked]);
		}
		if (category == "Textures")
		{
			m_selectedTextures.push_back(nodeClicked);
			editor->GetPropertyEditor()->AddTexture2D(editor->GetDemo()->GetTextures()[nodeClicked]);
		}
		if (category == "Shaders")
		{
			m_selectedShaders.push_back(nodeClicked);
			editor->GetPropertyEditor()->AddShaderProgram(editor->GetDemo()->GetShaders()[nodeClicked]);
		}
	}

	ImGui::End();
}

void Assets::LoadAsset(std::string file)
{
	editor->GetConsole()->Log(file.c_str());
	editor->GetConsole()->Log("\n");
}
