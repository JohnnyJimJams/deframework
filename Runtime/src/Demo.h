#ifndef __DEMO_H_
#define __DEMO_H_

#include <GL/gl3w.h> 
#include "Texture2D.h"

class Demo
{
public:
	Demo(unsigned int width, unsigned int height);
	virtual ~Demo();

	unsigned int GetWidth();
	unsigned int GetHeight();
	void DrawFullScreenQuad();
	Texture2D *GetCurrentFrame();
private:
	unsigned int m_width;
	unsigned int m_height;
	GLuint m_fullScreenQuadVAO, m_fullScreenQuadVBO, m_fullScreenQuadIBO;


	void PrepareFullScreenQuad();

};

#endif // __DEMO_H_