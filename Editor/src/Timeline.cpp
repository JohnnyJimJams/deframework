#include "Timeline.h"
#include "Editor.h"

Timeline::Timeline(Editor *peditor)
{
	editor = peditor;

	/*
	m_bar = TwNewBar("barTimeline");
	TwDefine(" barTimeline label='Timeline' ");
	TwDefine(" barTimeline resizable=false ");
	unsigned int edWidth = editor->GetWidth();
	unsigned int edHeight = editor->GetHeight();
	unsigned int margin = 20;

	unsigned int size[2];
	size[0] = edWidth - 2 * margin;
	size[1] = 50;
	TwSetParam(m_bar, NULL, "size", TW_PARAM_INT32, 2, size);

	unsigned int valuesWidth = size[0];
	TwSetParam(m_bar, NULL, "valueswidth", TW_PARAM_INT32, 1, &valuesWidth);

	unsigned int pos[2];
	pos[0] = margin + 5;
	pos[1] = edHeight - margin * 2 - 155 - 50;
	TwSetParam(m_bar, NULL, "position", TW_PARAM_INT32, 2, pos);
	*/
}

Timeline::~Timeline()
{
}

void Timeline::DrawBar()
{
}

void Timeline::TickUI(bool* p_open)
{
	if (!ImGui::Begin("Timeline", p_open))
	{
		ImGui::End();
		return;
	}
	ImGui::End();
}
