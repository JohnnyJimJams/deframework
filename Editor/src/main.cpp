#include <Windows.h>
#include "Editor.h"

INT __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	Editor *editor = new Editor(1280, 960);
	editor->Start();

	return 0;
}
