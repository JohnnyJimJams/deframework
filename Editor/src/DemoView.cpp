#include "DemoView.h"
#include "Editor.h"
#include "Texture2D.h"

DemoView::DemoView(Editor *peditor)
{
	editor = peditor;

	m_texture = new Texture2D("..\\Editor\\resources\\smiley.jpg");

	// setup shaderprogram
	m_shader = new ShaderProgram();
	m_shader->CompileFromFile(GL_VERTEX_SHADER, "..\\Editor\\resources\\layer.vert");
	m_shader->CompileFromFile(GL_FRAGMENT_SHADER, "..\\Editor\\resources\\layer.frag");
	m_shader->LinkProgram();
	uniTime = m_shader->GetUniform("time");
	uniResolution = m_shader->GetUniform("resolution");

	// set up framebuffer
	m_fbo = new FrameBuffer(editor->GetDemo()->GetWidth(), editor->GetDemo()->GetHeight());

	m_mesh = new Mesh("..\\Editor\\resources\\suzanne.glb");
}

DemoView::~DemoView()
{
	delete m_texture;
	delete m_shader;
	delete m_fbo;
	delete m_mesh;
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
	glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);
	glDisable(GL_BLEND);
	m_shader->Bind();
	glUniform1f(uniTime, (float)editor->GetMusicSecondsNow());
	glUniform2f(uniResolution, (float)editor->GetDemo()->GetWidth(), (float)editor->GetDemo()->GetHeight());
	editor->GetDemo()->DrawFullScreenQuad();
	m_shader->Unbind();
	m_fbo->Unbind();	

	// render texture from framebuffer
	ImGui::Image((ImTextureID)m_fbo->GetColorTexture()->GetId(), windowSize);

	ImGui::End();
}
