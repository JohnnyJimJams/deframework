#pragma once
#include "imgui/imgui.h"
#include "Animation.h"
#include <vector>

class Editor;

class DopeSheet
{
public:
	DopeSheet(Editor *editor);
	virtual ~DopeSheet();

	Editor *editor;
	void TickUI(bool* p_open = NULL);
	void Init();

	std::vector<Animation> animations;
	bool keymebool;
	int keymeint;
	float keymefloat;
	double keymedouble;
private:
};