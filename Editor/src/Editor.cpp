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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, "Defame Editor", NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);

	// OpenGL loader
	gl3wInit();

	m_demo = new Demo(m_width, m_height, L"..\\Editor\\resources\\TDIME.mp3");
	m_console = new Console(this);
	m_toolbar = new Toolbar(this);
	m_timeline = new Timeline(this);
	m_curveeditor = new CurveEditor(this);
	m_dopesheet = new DopeSheet(this);
	m_propertyeditor = new PropertyEditor(this);
	m_assets = new Assets(this);

	m_demoview = new DemoView(this);

	glfwSetKeyCallback(m_window, glfw_key_callback);
	glfwSetCharCallback(m_window, glfw_char_callback);
	glfwSetMouseButtonCallback(m_window, glfw_mousebutton_callback);
	glfwSetCursorPosCallback(m_window, glfw_mousepos_callback);
	glfwSetScrollCallback(m_window, glfw_mousewheel_callback);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Editor Main loop!
	bool show_demo_window = true;
	m_console->Log("Start main loop\n");
	while (!glfwWindowShouldClose(m_window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow(&show_demo_window);
		TickUI();
		if (m_mode == EditorMode::Play) m_demo->Tick(m_demo->GetMusicSecondsNow());

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwMakeContextCurrent(m_window);
		glfwGetFramebufferSize(m_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
	// Cleanup
	delete m_console;
	delete m_toolbar;
	delete m_timeline;
	delete m_curveeditor;
	delete m_dopesheet;
	delete m_demoview;
	delete m_propertyeditor;
	delete m_assets;
	delete m_demo;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
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
		__int64 end = m_demo->GetAudio()->GetDuration();

		m_demo->GetAudio()->SetPositions(&start, &end, true);
		m_console->Log("Restart\n");
		return;
	}
	if ( m_mode == EditorMode::Edit)
	{
		m_mode = EditorMode::Play;
		m_demo->GetAudio()->Play();
		m_console->Log("Play from current position\n");
		return;
	}
}

void Editor::Stop()
{
	if (m_mode == EditorMode::Play)
	{
		m_mode = EditorMode::Edit;
		m_demo->GetAudio()->Stop();
		m_console->Log("Stop\n");
		return;
	}
}

double Editor::GetMusicSecondsNow()
{
	return m_demo->GetMusicSecondsNow();
}

void Editor::SetMusicSeconds(double time)
{
	__int64 start =(__int64) (time * 10000000.0);
	__int64 end = m_demo->GetAudio()->GetDuration();

	m_demo->GetAudio()->SetPositions(&start, &end, true);
}

double Editor::GetMusicSecondsTotal()
{
	return m_demo->GetMusicSecondsTotal();
}

Console * Editor::GetConsole()
{
	return m_console;
}

CurveEditor * Editor::GetCurveEditor()
{
	return m_curveeditor;
}

Demo * Editor::GetDemo()
{
	return m_demo;
}


void Editor::TickUI()
{
	m_console->TickUI();
	m_toolbar->TickUI();
	m_timeline->TickUI();
	m_dopesheet->TickUI();
	m_curveeditor->TickUI();
	m_demoview->TickUI();
	m_propertyeditor->TickUI();
	m_assets->TickUI();
}

void Editor::glfw_error_callback(int error, const char * description)
{
}

void Editor::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
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
