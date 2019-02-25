#pragma once
#include "imgui/imgui.h"

class Editor;

class Timeline
{
public:
	Timeline(Editor *editor);
	virtual ~Timeline();

	Editor *editor;
	void DrawBar();
	void TickUI(bool* p_open = NULL);
private:
};