#include "DemoView.h"
#include "Editor.h"
#include "Texture2D.h"
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

DemoView::DemoView(Editor *peditor)
{
	editor = peditor;

	m_texture = new Texture2D("..\\Editor\\resources\\smiley.jpg");

	// setup shaderprogram
	m_shaderFullScreenQuad = new ShaderProgram();
	m_shaderFullScreenQuad->CompileFromFile(GL_VERTEX_SHADER, "..\\Editor\\resources\\layer.vert");
	m_shaderFullScreenQuad->CompileFromFile(GL_FRAGMENT_SHADER, "..\\Editor\\resources\\layer.frag");
	m_shaderFullScreenQuad->LinkProgram();
	uniFullScreenQuadTime = m_shaderFullScreenQuad->GetUniform("time");
	uniFullScreenQuadResolution = m_shaderFullScreenQuad->GetUniform("resolution");

	m_shaderDefault = new ShaderProgram();
	m_shaderDefault->CompileFromFile(GL_VERTEX_SHADER, "..\\Editor\\resources\\default.vert");
	m_shaderDefault->CompileFromFile(GL_FRAGMENT_SHADER, "..\\Editor\\resources\\default.frag");
	m_shaderDefault->LinkProgram();
	uniDefaultTime = m_shaderDefault->GetUniform("time");
	uniDefaultResolution = m_shaderDefault->GetUniform("resolution");

	// set up framebuffer
	m_fbo = new FrameBuffer(editor->GetDemo()->GetWidth(), editor->GetDemo()->GetHeight());

	m_mesh = new Mesh("..\\Editor\\resources\\suzanne.glb");

	m_camera = new Camera();

	editor->GetConsole()->Log(m_mesh->GetLog().c_str());
}

DemoView::~DemoView()
{
	delete m_texture;
	delete m_shaderFullScreenQuad;
	delete m_fbo;
	delete m_mesh;
	delete m_camera;
}

void DemoView::TickUI(bool* p_open)
{
	if (!ImGui::Begin("Demo View", p_open))
	{
		ImGui::End();
		return;
	}
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec4 backGroundCol = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	const ImU32 col32 = ImColor(backGroundCol);
	ImVec2 windowPos = ImGui::GetCursorScreenPos();
	ImVec2 windowSize = ImGui::GetContentRegionAvail();

	// Draw background colour
	//draw_list->AddRectFilled(windowPos, ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y), col32);

	m_fbo->Bind();

	//m_shaderFullScreenQuad->Bind();
	//glUniform1f(uniFullScreenQuadTime, (float)editor->GetMusicSecondsNow());
	//glUniform2f(uniFullScreenQuadResolution, (float)editor->GetDemo()->GetWidth(), (float)editor->GetDemo()->GetHeight());
	//editor->GetDemo()->DrawFullScreenQuad();
	//m_shaderFullScreenQuad->Unbind();


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	m_shaderDefault->Bind();
	// Setup uniforms (View, Projection)
	glm::mat4 Model = glm::mat4(1.0f);
	Model = glm::rotate(Model, (float)editor->GetMusicSecondsNow(), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.f);
	glm::mat4 View = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(m_shaderDefault->GetUniform("model"), 1, GL_FALSE, glm::value_ptr(Model));
	glUniformMatrix4fv(m_shaderDefault->GetUniform("view"), 1, GL_FALSE, glm::value_ptr(View));
	glUniformMatrix4fv(m_shaderDefault->GetUniform("projection"), 1, GL_FALSE, glm::value_ptr(Projection));
	m_mesh->Draw();
	glDisable(GL_DEPTH_TEST);
	m_shaderDefault->Unbind();

	m_fbo->Unbind();	

	// render texture from framebuffer
	ImGui::Image((ImTextureID)m_fbo->GetColorTexture()->GetId(), windowSize);

	ImGui::End();
}
