#ifndef __FRAMEBUFFER_H_
#define __FRAMEBUFFER_H_
#include "Texture2D.h"

class FrameBuffer
{
public:
	FrameBuffer(unsigned int width, unsigned int height);
	virtual ~FrameBuffer();
	void	Bind();
	void	Unbind();

	bool	IsBound() const { return m_bound; }
	unsigned int GetWidth();
	unsigned int GetHeight();
	Texture2D *GetColorTexture();

private:
	bool m_bound;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_fbo;
	unsigned int m_rbo;
	Texture2D *m_texColorBuffer;
};

#endif // __FRAMEBUFFER_H_