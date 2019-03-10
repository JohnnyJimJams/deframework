#pragma once
#include "imgui/imgui.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "FrameBuffer.h"
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

	Texture2D *m_texture;
	FrameBuffer *m_fbo;
	Mesh *m_mesh;
	Camera *m_camera;
};