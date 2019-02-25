#pragma once

class Editor;

class Timeline
{
public:
	Timeline(Editor *editor);
	virtual ~Timeline();

	Editor *editor;
	void DrawBar();
private:
};