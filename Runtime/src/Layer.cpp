#include "Layer.h"
#include <GL/gl3w.h> 

Layer::Layer(unsigned int width, unsigned int height, std::string pname)
{
	m_frameBuffer = new FrameBuffer(width, height);
	m_width = width;
	m_height = height;
	name = pname;
}

Layer::~Layer()
{
	delete m_frameBuffer;
}

void Layer::Bind()
{
	m_bound = true;
	m_frameBuffer->Bind();
}

void Layer::Unbind()
{
	m_bound = false;
	m_frameBuffer->Unbind();
}

unsigned int Layer::GetWidth()
{
	return m_width;
}

unsigned int Layer::GetHeight()
{
	return m_height;
}

Texture2D * Layer::GetColorTexture()
{
	return m_frameBuffer->GetColorTexture();
}
