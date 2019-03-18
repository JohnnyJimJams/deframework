#ifndef __LAYER_H_
#define __LAYER_H_
#include "Texture2D.h"
#include "FrameBuffer.h"
#include <vector>
#include "Entity.h"

class Layer
{
public:
	Layer(unsigned int width, unsigned int height, std::string name);
	virtual ~Layer();
	void	Bind();
	void	Unbind();

	bool	IsBound() const { return m_bound; }
	unsigned int GetWidth();
	unsigned int GetHeight();
	Texture2D *GetColorTexture();
	
	float opacity = 1.0f;
	bool enabled = true;
	std::string name = "";
	unsigned int order = 0;
	std::vector<Entity *> *GetEntities() { return &m_entities; }

private:
	bool m_bound;
	unsigned int m_width;
	unsigned int m_height;
	FrameBuffer *m_frameBuffer;
	std::vector<Entity *> m_entities;
};

#endif // __LAYER_H_