#include "Layer.h"
#include "Demo.h"

Demo::Demo(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;
	PrepareFullScreenQuad();
}

Demo::~Demo()
{
}

unsigned int Demo::GetWidth()
{
	return m_width;
}

unsigned int Demo::GetHeight()
{
	return m_height;
}

void Demo::DrawFullScreenQuad()
{
	glBindVertexArray(m_fullscreenQuadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

Texture2D * Demo::GetCurrentFrame()
{
	return nullptr;
}

void Demo::PrepareFullScreenQuad()
{
	float quad[] =
	{
		-1.0f,-1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f,-1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

		-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,-1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	};
	glGenVertexArrays(1, &m_fullscreenQuadVAO);
	glBindVertexArray(m_fullscreenQuadVAO);
	glGenBuffers(1, &m_fullscreenQuadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_fullscreenQuadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 5 * 6, quad, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, ((char*)0) + 12);
	glBindVertexArray(0);
}

