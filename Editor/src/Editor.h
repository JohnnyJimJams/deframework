#pragma once

#include <GLFW/glfw3.h>
#include <AntTweakBar.h>

class Editor
{
public:
	Editor();
	virtual ~Editor();

	void Start();
private:
	GLFWwindow* m_window;
	TwBar *Console;
	unsigned int m_width;
	unsigned int m_height;

	static void glfw_error_callback(int error, const char* description);
	static void glfw_key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	static void glfw_char_callback(GLFWwindow * window, unsigned int codepoint);
	static void glfw_mousebutton_callback(GLFWwindow* window, int button, int action, int mods);
	static void glfw_mousepos_callback(GLFWwindow* window, double xpos, double ypos);
	static void glfw_mousewheel_callback(GLFWwindow* window, double xoffset, double yoffset);
};

