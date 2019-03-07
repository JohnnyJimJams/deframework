#ifndef __LAYER_H_
#define __LAYER_H_
#include "Texture2D.h"
#include "FrameBuffer.h"

class Layer
{
public:
	Layer(unsigned int width, unsigned int height);
	virtual ~Layer();
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
	FrameBuffer *m_frameBuffer;
};

#endif // __LAYER_H_