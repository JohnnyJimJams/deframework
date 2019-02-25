#include "Editor.h"

Editor::Editor(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;

	m_mode = EditorMode::Edit;
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
	m_window = glfwCreateWindow(m_width, m_height, "Defame Editor", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);

	// Audio!
	audio = new Mp3();
	audio->Load(L"C:\\Users\\Alienware\\Desktop\\Demoscene\\deframework2_demoExample\\sample_orig.mp3");

	m_console = new Console(this);
	m_toolbar = new Toolbar(this);
	m_timeline = new Timeline(this);

	glfwSetKeyCallback(m_window, glfw_key_callback);
	glfwSetCharCallback(m_window, glfw_char_callback);
	glfwSetMouseButtonCallback(m_window, glfw_mousebutton_callback);
	glfwSetCursorPosCallback(m_window, glfw_mousepos_callback);
	glfwSetScrollCallback(m_window, glfw_mousewheel_callback);
	
	m_console->Log("Start main loop..");

	// Editor Main loop!
	while (!glfwWindowShouldClose(m_window))
	{
		glViewport(0, 0, m_width, m_height);
		glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		m_timeline->DrawBar();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
	glfwDestroyWindow(m_window);
}

void Editor::SetBackgroundColor(float r, float g, float b)
{
	m_backgroundColor[0] = r;
	m_backgroundColor[1] = g;
	m_backgroundColor[2] = b;
}

unsigned int Editor::GetWidth()
{
	return m_width;
}

unsigned int Editor::GetHeight()
{
	return m_height;
}

void Editor::Play()
{
	if (m_mode == EditorMode::Play)
	{
		__int64 start = 0;
		__int64 end = audio->GetDuration();

		audio->SetPositions(&start, &end, true);
		//audio->Play();
		return;
	}
	if ( m_mode == EditorMode::Edit)
	{
		m_mode = EditorMode::Play;
		audio->Play();
		return;
	}
}

void Editor::Stop()
{
	if (m_mode == EditorMode::Play)
	{
		m_mode = EditorMode::Edit;
		audio->Stop();
		return;
	}
}

Console * Editor::GetConsole()
{
	return m_console;
}


void Editor::glfw_error_callback(int error, const char * description)
{
}

void Editor::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Editor::glfw_char_callback(GLFWwindow * window, unsigned int codepoint)
{
}

void Editor::glfw_mousebutton_callback(GLFWwindow * window, int button, int action, int mods)
{
}

void Editor::glfw_mousepos_callback(GLFWwindow * window, double xpos, double ypos)
{
}

void Editor::glfw_mousewheel_callback(GLFWwindow * window, double xoffset, double yoffset)
{
}
