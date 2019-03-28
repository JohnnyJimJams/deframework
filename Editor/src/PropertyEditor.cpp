#include "PropertyEditor.h"
#include "Editor.h"
#include "imgui/misc/cpp/imgui_stdlib.h"


PropertyEditor::PropertyEditor(Editor *peditor)
{
	editor = peditor;
}

PropertyEditor::~PropertyEditor()
{
}

void PropertyEditor::TickUI(bool* p_open)
{
	if (!ImGui::Begin("Properties", p_open))
	{
		ImGui::End();
		return;
	}

	int entCount = m_entities.size();
	int texCount = m_textures.size();
	int shdCount = m_shaders.size();
	int matCount = m_materials.size();
	int mesCount = m_meshes.size();
	int totalCount = entCount + texCount + shdCount + matCount + mesCount;
	
	if (entCount>0 && (totalCount - entCount)==0)	// only entities selected
	{
		for (auto e : m_entities)
		{
			ImGui::InputText("Name", &e->Name);
			ImGui::Checkbox("Active", &e->Active);
			ImGui::SliderFloat3("Position", (float*)&e->Position, -10.0f, 10.0f);
			glm::vec3 euler = degrees(e->GetEulerAngles());
			ImGui::SliderFloat3("Rotation", (float *)&euler, -179.999f, 179.999f);
			e->SetEulerAngles(radians(euler));
			ImGui::SliderFloat3("Scale", (float*)&e->Scale, -10.0f, 10.0f);
			ImGui::Separator();
		}
	}

	if (texCount > 0 && (totalCount - texCount) == 0)	// only textures
	{
		for (auto t : m_textures)
		{
			std::string oldName = editor->GetDemo()->GetTexture2DName(t);
			std::string name = editor->GetDemo()->GetTexture2DName(t);
			ImGui::InputText("Name", &name);
			if (name != oldName)
			{
				// Handle rename asset
				if (editor->GetDemo()->Texture2DNameExists(name))
				{
					editor->GetConsole()->Log("Unable to rename, an asset with this name already exists.\n");
				}
				else
				{
					editor->GetDemo()->GetTextures().erase(oldName);
					editor->GetDemo()->AddTexture2D(name, t);
				}
			}
			ImGui::Separator();
		}
	}

	if (shdCount > 0 && (totalCount - shdCount) == 0)	// only shaders
	{
		for (auto s : m_shaders)
		{
			ImGui::Separator();
		}
	}

	if (matCount > 0 && (totalCount - matCount) == 0)	// only materials
	{
		for (auto m : m_materials)
		{
			ImGui::Separator();
		}
	}

	if (mesCount > 0 && (totalCount - mesCount) == 0)	// only meshes
	{
		for (auto m : m_meshes)
		{
			ImGui::Separator();
		}
	}


	ImGui::End();
}

void PropertyEditor::AddEntity(Entity * entity)
{
	if (std::find(m_entities.begin(), m_entities.end(), entity) == m_entities.end()) m_entities.push_back(entity);
}

void PropertyEditor::ClearEntities()
{
	m_entities.clear();
}

void PropertyEditor::AddMesh(Mesh * mesh)
{
	if (std::find(m_meshes.begin(), m_meshes.end(), mesh) == m_meshes.end()) m_meshes.push_back(mesh);
}

void PropertyEditor::ClearMeshes()
{
	m_meshes.clear();
}

void PropertyEditor::AddMaterial(Material * material)
{
	if (std::find(m_materials.begin(), m_materials.end(), material) == m_materials.end()) m_materials.push_back(material);
}

void PropertyEditor::ClearMaterials()
{
	m_materials.clear();
}

void PropertyEditor::AddTexture2D(Texture2D * texture)
{
	if (std::find(m_textures.begin(), m_textures.end(), texture) == m_textures.end()) m_textures.push_back(texture);
}

void PropertyEditor::ClearTextures()
{
	m_textures.clear();
}

void PropertyEditor::AddShaderProgram(ShaderProgram * shader)
{
	if (std::find(m_shaders.begin(), m_shaders.end(), shader) == m_shaders.end()) m_shaders.push_back(shader);
}

void PropertyEditor::ClearShaders()
{
	m_shaders.clear();
}

void PropertyEditor::AddLayer(Layer * layer)
{
	if (std::find(m_layers.begin(), m_layers.end(), layer) == m_layers.end()) m_layers.push_back(layer);
}

void PropertyEditor::ClearLayers()
{
	m_layers.clear();
}

void PropertyEditor::ClearAll()
{
	ClearEntities();
	ClearMaterials();
	ClearMeshes();
	ClearTextures();
	ClearShaders();
}
