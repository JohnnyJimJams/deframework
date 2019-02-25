#pragma once

class Editor;

class Toolbar
{
public:
	Toolbar(Editor *editor);
	virtual ~Toolbar();

	Editor *editor;

private:
};