#include <Windows.h>
#include "Editor.h"
#include "winuser.h"

INT __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	int desktopWidth = GetSystemMetrics(SM_CXSCREEN);
	int desktopHeight = GetSystemMetrics(SM_CYSCREEN);

	Editor *editor = new Editor(desktopWidth-200, desktopHeight-200); // These functions don't handle windows 10 display scaling
	editor->Start();

	return 0;
}
