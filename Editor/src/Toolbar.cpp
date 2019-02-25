#include "Toolbar.h"
#include "Editor.h"

Toolbar::Toolbar(Editor *peditor)
{
	editor = peditor;
/*
	m_bar = TwNewBar("barToolbar");
	TwDefine(" barToolbar label='Toolbar' ");
	TwDefine(" barToolbar resizable=false ");
	unsigned int edWidth = editor->GetWidth();
	unsigned int edHeight = editor->GetHeight();
	unsigned int margin = 20;

	unsigned int size[2];
	size[0] = 130;
	size[1] = 300;
	TwSetParam(m_bar, NULL, "size", TW_PARAM_INT32, 2, size);

	unsigned int valuesWidth = 20;
	TwSetParam(m_bar, NULL, "valueswidth", TW_PARAM_INT32, 1, &valuesWidth);

	unsigned int pos[2];
	pos[0] = margin + 5;
	pos[1] = margin;
	TwSetParam(m_bar, NULL, "position", TW_PARAM_INT32, 2, pos);

	TwAddButton(m_bar, "btnPlay", playClicked, this, " label='Play' ");
	TwAddButton(m_bar, "btnStop", stopClicked, this, " label='Stop' ");
	*/
}

Toolbar::~Toolbar()
{
}

/*
void TW_CALL Toolbar::playClicked(void * clientData)
{
	((Toolbar *)clientData)->editor->Play();
}

void TW_CALL Toolbar::stopClicked(void * clientData)
{
	((Toolbar *)clientData)->editor->Stop();
}
*/