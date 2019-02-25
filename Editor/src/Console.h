#pragma once
#include <iostream>
#include "imgui/imgui.h"

class Editor;

class Console
{
public:
	Console(Editor *editor);
	virtual ~Console();
	void Clear();
	Editor *editor;
	void Log(const char* fmt, ...) IM_FMTARGS(2);
	void TickUI(bool* p_open = NULL);
private:
	ImGuiTextBuffer     Buf;
	ImGuiTextFilter     Filter;
	ImVector<int>       LineOffsets;        // Index to lines offset. We maintain this with AddLog() calls, allowing us to have a random access on lines
	bool                AutoScroll;
	bool                ScrollToBottom;

	
};