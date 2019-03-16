#include "FrameBuffer.h"
#include <GL/gl3w.h> 

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
{
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	m_width = width;
	m_height = height;
	m_texColorBuffer = new Texture2D(width, height, 3);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texColorBuffer->GetId(), 0);

	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		int i = 0;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	delete m_texColorBuffer;
}

void FrameBuffer::Bind()
{
	m_bound = true;
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void FrameBuffer::Unbind()
{
	m_bound = false;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int FrameBuffer::GetWidth()
{
	return m_width;
}

unsigned int FrameBuffer::GetHeight()
{
	return m_height;
}

Texture2D * FrameBuffer::GetColorTexture()
{
	return m_texColorBuffer;
}
