#pragma once
#include "imgui/imgui.h"

class Editor;

class Toolbar
{
public:
	Toolbar(Editor *editor);
	virtual ~Toolbar();

	Editor *editor;
	void TickUI(bool* p_open = NULL);
private:
};