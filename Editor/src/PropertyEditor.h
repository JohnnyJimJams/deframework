#pragma once
#include "imgui/imgui.h"
#include "Entity.h"
#include "Mesh.h"
#include "Material.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Layer.h"
#include <vector>

class Editor;

class PropertyEditor
{
public:
	PropertyEditor(Editor *editor);
	virtual ~PropertyEditor();

	Editor *editor;
	void TickUI(bool* p_open = NULL);
	void AddEntity(Entity *entity);
	void ClearEntities();
	void AddMesh(Mesh *mesh);
	void ClearMeshes();
	void AddMaterial(Material *material);
	void ClearMaterials();
	void AddTexture2D(Texture2D *texture);
	void ClearTextures();
	void AddShaderProgram(ShaderProgram *shader);
	void ClearShaders();
	void AddLayer(Layer *layer);
	void ClearLayers();
	void ClearAll();
private:
	std::vector<Entity *>m_entities;
	std::vector<Layer *>m_layers;
	std::vector<Mesh *>m_meshes;
	std::vector<Material *>m_materials;
	std::vector<ShaderProgram *>m_shaders;
	std::vector<Texture2D *>m_textures;
};