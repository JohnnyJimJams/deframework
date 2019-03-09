#include "Texture2D.h"
#include <GL/gl3w.h> 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture2D::Texture2D(unsigned int width, unsigned int height, unsigned int channels, unsigned char * data)
{
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
	m_height = height;
	m_width = width;
	m_channels = channels;
	glTexImage2D(GL_TEXTURE_2D, 0, channels == 3 ? GL_RGB : GL_RGBA, width, height, 0, channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//SetParamater(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	SetParamater(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	SetParamater(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	SetParamater(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	SetParamater(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture2D::Texture2D(const char * filename)
{
	int width, height, channels;
	unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);
	if (data)
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		m_height = height;
		m_width = width;
		m_channels = channels;
		glTexImage2D(GL_TEXTURE_2D, 0, channels == 3 ? GL_RGB : GL_RGBA, width, height, 0, channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		SetParamater(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		SetParamater(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		SetParamater(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		SetParamater(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(data);
	}
	else
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);
		m_height = height;
		m_width = width;
		m_channels = channels;
		glTexImage2D(GL_TEXTURE_2D, 0, channels == 3 ? GL_RGB : GL_RGBA, width, height, 0, channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glGenerateMipmap(GL_TEXTURE_2D);
		SetParamater(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		SetParamater(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		SetParamater(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		SetParamater(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
}

Texture2D::~Texture2D()
{
}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_id);
	m_bound = true;
}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	m_bound = false;
}

unsigned int Texture2D::GetWidth()
{
	return m_width;
}

unsigned int Texture2D::GetHeight()
{
	return m_height;
}

unsigned int Texture2D::GetChannels()
{
	return m_channels;
}

unsigned int Texture2D::GetId()
{
	return m_id;
}

void Texture2D::SetParamater(unsigned int name, unsigned int value)
{
	if (!IsBound()) Bind();
	glTexParameteri(GL_TEXTURE_2D, name, value);
}
