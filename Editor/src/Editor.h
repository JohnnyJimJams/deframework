#pragma once

#include <GLFW/glfw3.h>

class Editor
{
public:
	Editor();
	virtual ~Editor();

	void Start();
private:
	GLFWwindow* m_window;

	static void glfw_error_callback(int error, const char* description);
	static void glfw_key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
};

