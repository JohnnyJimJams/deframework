#include "DemoView.h"
#include "Editor.h"
#include "Texture2D.h"

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
	uniDefaultProjectionView = m_shaderDefault->GetUniform("projectionview");

	// set up framebuffer
	m_fbo = new FrameBuffer(editor->GetDemo()->GetWidth(), editor->GetDemo()->GetHeight());

	m_mesh = new Mesh("..\\Editor\\resources\\suzanne.glb");

	m_camera = new Camera();
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

	m_shaderFullScreenQuad->Bind();
	glUniform1f(uniFullScreenQuadTime, (float)editor->GetMusicSecondsNow());
	glUniform2f(uniFullScreenQuadResolution, (float)editor->GetDemo()->GetWidth(), (float)editor->GetDemo()->GetHeight());
	editor->GetDemo()->DrawFullScreenQuad();
	m_shaderFullScreenQuad->Unbind();

	/*
	glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);
	m_shaderDefault->Bind();
	// Setup uniforms (View, Projection)

	m_mesh->Draw();
	m_shaderDefault->Unbind();
	*/

	m_fbo->Unbind();	

	// render texture from framebuffer
	ImGui::Image((ImTextureID)m_fbo->GetColorTexture()->GetId(), windowSize);

	ImGui::End();
}
