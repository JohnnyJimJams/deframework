#pragma once
#include "imgui/imgui.h"

#include <vector>
#include <string>

class Editor;

class Assets
{
public:
	Assets(Editor *editor);
	virtual ~Assets();

	Editor *editor;
	void TickUI(bool* p_open = NULL);
	void LoadAsset(std::string file);
private:
	std::vector<std::string> m_selectedMeshes;
	std::vector<std::string> m_selectedTextures;
	std::vector<std::string> m_selectedShaders;
	std::vector<std::string> m_selectedMaterials;
};