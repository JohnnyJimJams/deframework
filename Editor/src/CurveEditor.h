#pragma once
#include "imgui/imgui.h"
#include "Animation.h"

class Editor;

class CurveEditor
{
public:
	CurveEditor(Editor *editor);
	virtual ~CurveEditor();

	Editor *editor;
	void TickUI(bool* p_open = NULL);
	Animation *animation = NULL;
private:
};