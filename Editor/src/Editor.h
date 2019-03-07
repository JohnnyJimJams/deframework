#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#include "MP3.h"
#include "Console.h"
#include "Toolbar.h"
#include "Timeline.h"
#include "DopeSheet.h"
#include "CurveEditor.h"
#include "DemoView.h"
#include "Demo.h"
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#include <GLFW/glfw3.h>

enum EditorMode { Edit, Play };

class Editor
{
public:
	Editor(unsigned int width, unsigned int height);
	virtual ~Editor();

	void Start();
	void SetBackgroundColor(float r, float g, float b);
	unsigned int GetWidth();
	unsigned int GetHeight();
	void Play();
	void Stop();
	double GetMusicSecondsNow();
	void SetMusicSeconds(double time);
	double GetMusicSecondsTotal();
	Console *GetConsole();
	CurveEditor *GetCurveEditor();
	Demo *GetDemo();

private:
	GLFWwindow* m_window;
	Console *m_console;
	Toolbar *m_toolbar;
	Timeline *m_timeline;
	DopeSheet *m_dopesheet;
	CurveEditor *m_curveeditor;
	DemoView *m_demoview;
	Demo *m_demo;
	unsigned int m_width;
	unsigned int m_height;
	GLfloat m_backgroundColor[3] = { .02f, .02f, 0.05f };
	Mp3 *audio;
	EditorMode m_mode;
	void TickUI();

	static void glfw_error_callback(int error, const char* description);
	static void glfw_key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	static void glfw_char_callback(GLFWwindow * window, unsigned int codepoint);
	static void glfw_mousebutton_callback(GLFWwindow* window, int button, int action, int mods);
	static void glfw_mousepos_callback(GLFWwindow* window, double xpos, double ypos);
	static void glfw_mousewheel_callback(GLFWwindow* window, double xoffset, double yoffset);
};

