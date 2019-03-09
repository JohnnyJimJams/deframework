#ifndef __SHADERPROGRAM_H_
#define __SHADERPROGRAM_H_

#include <map>

class ShaderProgram
{
public:

	ShaderProgram();
	virtual ~ShaderProgram();

	void	Bind();
	void	Unbind();

	bool	isBound() const	{	return m_bound;	}

	void	CompileFromFile(unsigned int a_type, const char* a_filename);
	void	CompileFromString(unsigned int a_type, const char* a_shader);
	void	CompileFromStrings(unsigned int a_type, unsigned int a_stringCount, const char** a_shaderStrings);

	bool	LinkProgram();

	int		GetUniform(const char* a_uniform);

	unsigned int	GetProgram() const					{	return m_program;			}
	unsigned int	GetShader(unsigned int a_type)		{	return m_shaders[a_type];	}

	static ShaderProgram*	GetCurrentBoundProgram()	{	return sm_boundProgram;		}

protected:

	bool			m_bound;
	unsigned int	m_program;

	std::map<unsigned int,unsigned int>	m_shaders;

	static ShaderProgram*	sm_boundProgram;
};

#endif // __SHADERPROGRAM_H_