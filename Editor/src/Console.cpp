#include "Console.h"
#include "Editor.h"

Console::Console(Editor *peditor)
{
	editor = peditor;
/*
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
*/
}

Console::~Console()
{
}

void Console::ClearConsole()
{
}

void Console::Log(std::string message)
{
}
