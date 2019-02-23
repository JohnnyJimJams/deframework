#pragma once

#include <AntTweakBar.h>

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
	TwBar *m_bar;

	std::string m_ConsoleText;

	std::string m_ConsoleLine1;
	std::string m_ConsoleLine2;
	std::string m_ConsoleLine3;
	std::string m_ConsoleLine4;
	std::string m_ConsoleLine5;
	std::string m_ConsoleLine6;

	static void TW_CALL clearConsoleClicked(void * clientData);
	static void TW_CALL CopyStdStringToClient(std::string& destinationClientString, const std::string& sourceLibraryString);
	static void TW_CALL TWGetm_ConsoleLine1(void *value, void * clientData);
	static void TW_CALL TWGetm_ConsoleLine2(void *value, void * clientData);
	static void TW_CALL TWGetm_ConsoleLine3(void *value, void * clientData);
	static void TW_CALL TWGetm_ConsoleLine4(void *value, void * clientData);
	static void TW_CALL TWGetm_ConsoleLine5(void *value, void * clientData);
	static void TW_CALL TWGetm_ConsoleLine6(void *value, void * clientData);
	static void TW_CALL TWSetm_ConsoleLine(const void *value, void *clientData);

	std::string GetConsoleLine1();
	std::string GetConsoleLine2();
	std::string GetConsoleLine3();
	std::string GetConsoleLine4();
	std::string GetConsoleLine5();
	std::string GetConsoleLine6();
	void SetConsoleLine1(const std::string value);
	void SetConsoleLine2(const std::string value);
	void SetConsoleLine3(const std::string value);
	void SetConsoleLine4(const std::string value);
	void SetConsoleLine5(const std::string value);
	void SetConsoleLine6(const std::string value);
};