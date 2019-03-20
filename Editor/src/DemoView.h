#pragma once
#include "imgui/imgui.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Layer.h"
#include "Mesh.h"
#include "Camera.h"

class Editor;

class DemoView
{
public:
	DemoView(Editor *editor);
	virtual ~DemoView();

	Editor *editor;
	void TickUI(bool* p_open = NULL);
private:
	ShaderProgram *m_shaderFullScreenQuad;
	unsigned int uniFullScreenQuadTime;
	unsigned int uniFullScreenQuadResolution;
	
	ShaderProgram *m_shaderDefault;
	unsigned int uniDefaultTime;
	unsigned int uniDefaultResolution;
	unsigned int uniDefaultProjectionView;
	Layer *m_layer;
	Texture2D *m_texture;
	Mesh *m_mesh;
	Camera *m_camera;
	Entity *m_entity;
};