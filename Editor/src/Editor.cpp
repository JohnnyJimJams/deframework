#include "Editor.h"

Editor::Editor()
{
}

Editor::~Editor()
{
}

void Editor::Start()
{
	// Editor Init
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	m_window = glfwCreateWindow(1280, 960, "Defame Editor", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		return;
	}

	glfwSetKeyCallback(m_window, glfw_key_callback);
	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);

	// Editor Main loop!
	while (!glfwWindowShouldClose(m_window))
	{
		int width, height;
		glfwGetFramebufferSize(m_window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
	glfwDestroyWindow(m_window);
}

void Editor::glfw_error_callback(int error, const char * description)
{
}

void Editor::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
