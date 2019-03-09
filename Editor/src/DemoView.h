#pragma once
#include "imgui/imgui.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "FrameBuffer.h"

class Editor;

class DemoView
{
public:
	DemoView(Editor *editor);
	virtual ~DemoView();

	Editor *editor;
	void TickUI(bool* p_open = NULL);
private:
	ShaderProgram *m_shader;
	Texture2D *m_texture;
	FrameBuffer *m_fbo;
	unsigned int uniTime;
	unsigned int uniResolution;
};