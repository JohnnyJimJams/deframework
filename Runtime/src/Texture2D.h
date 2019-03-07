#ifndef __TEXTURE2D_H_
#define __TEXTURE2D_H_

class Texture2D
{
public:

	Texture2D(unsigned int width, unsigned int height, unsigned int channels, unsigned char *data = nullptr);
	Texture2D(const char *filename);
	~Texture2D();

	void	Bind();
	void	Unbind();

	bool	IsBound() const	{	return m_bound;	}
	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int GetChannels();
	unsigned int GetId();
	void SetParamater(unsigned int name, unsigned int value);
//protected:
	bool m_bound;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_channels;
	unsigned int m_id;
};

#endif // __TEXTURE2D_H_