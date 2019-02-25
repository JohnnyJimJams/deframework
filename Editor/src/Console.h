#pragma once
#include <iostream>

class Editor;

class Console
{
public:
	Console(Editor *editor);
	virtual ~Console();
	void ClearConsole();
	Editor *editor;
	void Log(std::string message);
private:

	std::string m_ConsoleText;

};