#pragma once
#include "imgui/imgui.h"
#include "Entity.h"

class Editor;

class PropertyEditor
{
public:
	PropertyEditor(Editor *editor);
	virtual ~PropertyEditor();

	Editor *editor;
	void TickUI(bool* p_open = NULL);
	void SetEntity(Entity *entity);
	void ClearEntity();
private:
	Entity *m_entity;
};