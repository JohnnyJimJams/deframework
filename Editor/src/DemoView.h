#pragma once
#include "imgui/imgui.h"
#include "DemoView.h"

class Editor;

class DemoView
{
public:
	DemoView(Editor *editor);
	virtual ~DemoView();

	Editor *editor;
	void TickUI(bool* p_open = NULL);
private:
};