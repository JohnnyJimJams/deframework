#include "Console.h"
#include "Editor.h"

Console::Console(Editor *peditor)
{
	editor = peditor;
	m_bar = TwNewBar("barConsole");
	TwDefine(" barConsole label='Console' ");
	TwDefine(" barConsole resizable=false ");
	unsigned int edWidth = editor->GetWidth();
	unsigned int edHeight= editor->GetHeight();
	unsigned int margin = 20;

	unsigned int size[2];
	size[0] = edWidth - 2 * margin;
	size[1] = 155;
	TwSetParam(m_bar, NULL, "size", TW_PARAM_INT32, 2, size);

	unsigned int valuesWidth = size[0] - 95;
	TwSetParam(m_bar, NULL, "valueswidth", TW_PARAM_INT32, 1, &valuesWidth);

	unsigned int pos[2];
	pos[0] = margin + 5;
	pos[1] = edHeight - margin - 155;
	TwSetParam(m_bar, NULL, "position", TW_PARAM_INT32, 2, pos);

	TwAddButton(m_bar, "btnClearConsole", clearConsoleClicked, this, " label='Clear' ");	
	TwAddVarCB(m_bar, "txtConsole1", TW_TYPE_STDSTRING, TWSetm_ConsoleLine, TWGetm_ConsoleLine1, this, " label=' ' ");
	TwAddVarCB(m_bar, "txtConsole2", TW_TYPE_STDSTRING, TWSetm_ConsoleLine, TWGetm_ConsoleLine2, this, " label=' ' ");
	TwAddVarCB(m_bar, "txtConsole3", TW_TYPE_STDSTRING, TWSetm_ConsoleLine, TWGetm_ConsoleLine3, this, " label=' ' ");
	TwAddVarCB(m_bar, "txtConsole4", TW_TYPE_STDSTRING, TWSetm_ConsoleLine, TWGetm_ConsoleLine4, this, " label=' ' ");
	TwAddVarCB(m_bar, "txtConsole5", TW_TYPE_STDSTRING, TWSetm_ConsoleLine, TWGetm_ConsoleLine5, this, " label=' ' ");
	TwAddVarCB(m_bar, "txtConsole6", TW_TYPE_STDSTRING, TWSetm_ConsoleLine, TWGetm_ConsoleLine6, this, " label=' ' ");
	m_ConsoleLine1 = "";
	m_ConsoleLine2 = "";
	m_ConsoleLine3 = "";
	m_ConsoleLine4 = "";
	m_ConsoleLine5 = "";
	m_ConsoleLine6 = "";
}

Console::~Console()
{
}

void TW_CALL Console::clearConsoleClicked(void * clientData)
{
	((Console *)clientData)->ClearConsole();
}

void TW_CALL Console::CopyStdStringToClient(std::string & destinationClientString, const std::string & sourceLibraryString)
{
		destinationClientString = sourceLibraryString;
}

void TW_CALL Console::TWGetm_ConsoleLine1(void * value, void * clientData)
{
	std::string *destPtr = static_cast<std::string *>(value);
	TwCopyStdStringToLibrary(*destPtr, ((Console *)clientData)->GetConsoleLine1());
}
void TW_CALL Console::TWGetm_ConsoleLine2(void * value, void * clientData)
{
	std::string *destPtr = static_cast<std::string *>(value);
	TwCopyStdStringToLibrary(*destPtr, ((Console *)clientData)->GetConsoleLine2());
}
void TW_CALL Console::TWGetm_ConsoleLine3(void * value, void * clientData)
{
	std::string *destPtr = static_cast<std::string *>(value);
	TwCopyStdStringToLibrary(*destPtr, ((Console *)clientData)->GetConsoleLine3());
}
void TW_CALL Console::TWGetm_ConsoleLine4(void * value, void * clientData)
{
	std::string *destPtr = static_cast<std::string *>(value);
	TwCopyStdStringToLibrary(*destPtr, ((Console *)clientData)->GetConsoleLine4());
}
void TW_CALL Console::TWGetm_ConsoleLine5(void * value, void * clientData)
{
	std::string *destPtr = static_cast<std::string *>(value);
	TwCopyStdStringToLibrary(*destPtr, ((Console *)clientData)->GetConsoleLine5());
}
void TW_CALL Console::TWGetm_ConsoleLine6(void * value, void * clientData)
{
	std::string *destPtr = static_cast<std::string *>(value);
	TwCopyStdStringToLibrary(*destPtr, ((Console *)clientData)->GetConsoleLine6());
}

void TW_CALL Console::TWSetm_ConsoleLine(const void * value, void * clientData)
{
	// commented out cause these console fields are read only
	//const std::string *srcPtr = static_cast<const std::string *>(value);
	//((Console *)clientData)->SetConsoleLine(*srcPtr);
}

std::string Console::GetConsoleLine1()
{
	return m_ConsoleLine1;
}
std::string Console::GetConsoleLine2()
{
	return m_ConsoleLine2;
}
std::string Console::GetConsoleLine3()
{
	return m_ConsoleLine3;
}
std::string Console::GetConsoleLine4()
{
	return m_ConsoleLine4;
}
std::string Console::GetConsoleLine5()
{
	return m_ConsoleLine5;
}
std::string Console::GetConsoleLine6()
{
	return m_ConsoleLine6;
}

void Console::SetConsoleLine1(const std::string value)
{
	m_ConsoleLine1 = value;
}
void Console::SetConsoleLine2(const std::string value)
{
	m_ConsoleLine2 = value;
}
void Console::SetConsoleLine3(const std::string value)
{
	m_ConsoleLine3 = value;
}
void Console::SetConsoleLine4(const std::string value)
{
	m_ConsoleLine4 = value;
}
void Console::SetConsoleLine5(const std::string value)
{
	m_ConsoleLine5 = value;
}
void Console::SetConsoleLine6(const std::string value)
{
	m_ConsoleLine6 = value;
}

void Console::ClearConsole()
{
	SetConsoleLine1("");
	SetConsoleLine2("");
	SetConsoleLine3("");
	SetConsoleLine4("");
	SetConsoleLine5("");
	SetConsoleLine6("");
}

void Console::Log(std::string message)
{
	m_ConsoleText = message + "\n" + m_ConsoleText;

	SetConsoleLine6(GetConsoleLine5());
	SetConsoleLine5(GetConsoleLine4());
	SetConsoleLine4(GetConsoleLine3());
	SetConsoleLine3(GetConsoleLine2());
	SetConsoleLine2(GetConsoleLine1());
	SetConsoleLine1(message);
}
