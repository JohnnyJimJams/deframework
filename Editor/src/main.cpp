#include <Windows.h>
#include "Editor.h"

INT __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	Editor *editor = new Editor();

	editor->Start();

	return 0;
}
