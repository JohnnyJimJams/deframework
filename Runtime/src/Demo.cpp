#include "Layer.h"
#include "Demo.h"

Demo::Demo(unsigned int width, unsigned int height)
{
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

	glBindVertexArray(m_fullScreenQuadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Texture2D * Demo::GetCurrentFrame()
{
	return nullptr;
}

void Demo::PrepareFullScreenQuad()
{

	// generate and bind the vao
	glGenVertexArrays(1, &m_fullScreenQuadVAO);
	glBindVertexArray(m_fullScreenQuadVAO);

	// generate and bind the vertex buffer object
	glGenBuffers(1, &m_fullScreenQuadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_fullScreenQuadVBO);

	// data for a fullscreen quad (this time with texture coords)
	GLfloat vertexData[] = {
		//  X     Y     Z           U     V     
		   1.0f, 1.0f, 0.0f,       1.0f, 1.0f, // vertex 0
		  -1.0f, 1.0f, 0.0f,       0.0f, 1.0f, // vertex 1
		   1.0f,-1.0f, 0.0f,       1.0f, 0.0f, // vertex 2
		  -1.0f,-1.0f, 0.0f,       0.0f, 0.0f, // vertex 3
	}; // 4 vertices with 5 components (floats) each

	// fill with data
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 5, vertexData, GL_STATIC_DRAW);


	// set up generic attrib pointers
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (char*)0 + 0 * sizeof(GLfloat));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (char*)0 + 3 * sizeof(GLfloat));


	// generate and bind the index buffer object
	glGenBuffers(1, &m_fullScreenQuadIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_fullScreenQuadIBO);

	GLuint indexData[] = {
		0,1,2, // first triangle
		2,1,3, // second triangle
	};

	// fill with data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 2 * 3, indexData, GL_STATIC_DRAW);

	// "unbind" vao
	glBindVertexArray(0);
}
