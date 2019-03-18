#include "DemoView.h"
#include "Editor.h"
#include "Texture2D.h"
#include <glm/mat4x4.hpp> // mat4
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

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
	m_layer = editor->GetDemo()->AddLayer("layer1");


	m_mesh = new Mesh("..\\Editor\\resources\\suzanne.glb");

	m_camera = new Camera();

	editor->GetConsole()->Log(m_mesh->GetLog().c_str());
}

DemoView::~DemoView()
{
	delete m_texture;
	delete m_shaderFullScreenQuad;
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

	m_layer->Bind();
		//m_shaderFullScreenQuad->Bind();
		//glUniform1f(uniFullScreenQuadTime, (float)editor->GetMusicSecondsNow());
		//glUniform2f(uniFullScreenQuadResolution, (float)editor->GetDemo()->GetWidth(), (float)editor->GetDemo()->GetHeight());
		//editor->GetDemo()->DrawFullScreenQuad();
		//m_shaderFullScreenQuad->Unbind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_shaderDefault->Bind();
			glEnable(GL_DEPTH_TEST);
			mat4 Model = mat4(1.0f);
			Model = rotate(Model, radians(180.0f), vec3(0.0f, 0.0f, 1.0f));
			Model = rotate(Model, (float)editor->GetMusicSecondsNow() + 90.0f, vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(m_shaderDefault->GetUniform("model"), 1, GL_FALSE, value_ptr(Model));

			mat4 Projection = perspective(radians(45.0f), (float)editor->GetWidth() / (float)editor->GetHeight(), 0.1f, 1000.f);
			mat4 View = lookAt(vec3(0.0f, 0.0f, 2.5f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(m_shaderDefault->GetUniform("view"), 1, GL_FALSE, value_ptr(View));
			glUniformMatrix4fv(m_shaderDefault->GetUniform("projection"), 1, GL_FALSE, value_ptr(Projection));

			m_mesh->Draw();
			glDisable(GL_DEPTH_TEST);
		m_shaderDefault->Unbind();
	m_layer->Unbind();	

	// render texture from framebuffer
	ImGui::Image((ImTextureID)m_layer->GetColorTexture()->GetId(), windowSize);

	ImGui::End();
}
